using UnityEngine;
using System.Collections;
using System.Collections.Generic;
using UnityEngine.UI;

public class GameManager : MonoBehaviour {

	static int level = 1;

	public GameObject city;
	public GameObject missile;
	public GameObject counterMissile;

	public GameObject gameOver;
	public GameObject victory;
	public Text levelText;
	public Text statsText;

	public float levelWidth = 20;
	public float missileY = 0;
	public float cityY = 0;
	
	int missiles = 0;
	int counterMissiles = 0;

	float nextFire = 3;

	int counterMissileBase = 0;

	public Transform[] counterMissileBases;

	GameObject[] cities;

	List<GameObject> activeMissiles = new List<GameObject>();
	
	// Use this for initialization
	void Start () {
		cities = new GameObject[level];
		missiles = cities.Length*3;
		counterMissiles = missiles;

		for (int i = 0; i < cities.Length; i++) {
			var cityX = cities.Length > 1 ? (((float)i/(cities.Length-1))-0.5f)*levelWidth : 0;
			cities[i] = GameObject.Instantiate (city, new Vector3(cityX, cityY, 0), Quaternion.identity) as GameObject;
		}

		SetBase(0);

		levelText.text = "Level " + level;
	}

	void SetBase (int index) {
		Debug.Log ("Set base " + index);
		counterMissileBase = index;
		for (int i = 0; i < counterMissileBases.Length; i++) {
			counterMissileBases[i].GetComponent<Renderer>().material.color = new Color (0, 1, 0, index == i ? 1 : 0.5f);
		}
	}

	void UpdateStats () {
		string s = "Ammo: " + counterMissiles;
		s += "\nAlive cities: " +AliveCities();
		statsText.text = s;
	}

	int AliveCities () {
		int count = 0;
		for (int i = 0; i < cities.Length; i++) {
			count += cities[i] ? 1 : 0;
		}
		return count;
	}

	// Update is called once per frame
	void Update () {

		UpdateStats ();

		if (Time.time > nextFire && missiles > 0) {
			missiles--;
			FireMissile ();
			nextFire = Time.time + (Random.value*1.5f + 0.5f);
		}


		for (int i = 0; i < counterMissileBases.Length; i++) {
			if (Input.GetKeyDown (KeyCode.Alpha0 + i + 1)) {
				SetBase(i);
			}
		}

		if (Input.GetKeyDown (KeyCode.Mouse0) && counterMissiles > 0) {
			counterMissiles--;
			FireCounter (Camera.main.ScreenToWorldPoint (Input.mousePosition));
		}

		bool anyAlive = AliveCities () > 0;

		if (!anyAlive) {
			gameOver.SetActive (true);
			Time.timeScale = 0;
		} else {
			bool anyMissiles = false;
			for (int i = 0; i < activeMissiles.Count; i++) {
				anyMissiles = anyMissiles || activeMissiles[i];
			}

			if (!anyMissiles && missiles == 0) {
				StartCoroutine(Victory());
			}
		}
	}

	void FireCounter (Vector2 p) {
		var pos = counterMissileBases[counterMissileBase].position;
		pos.z = 0;
		var go = GameObject.Instantiate (counterMissile, pos, Quaternion.identity) as GameObject;
		go.transform.LookAt (p, Vector3.right);
		go.transform.Rotate (new Vector3(-90,0,-90));
		go.transform.Rotate (new Vector3(-90,0,0));
		SetSpeed(go);

		go.GetComponent<CounterMissile>().target = p;
	}

	void FireMissile () {

		var go = GameObject.Instantiate (missile, new Vector3((Random.value-0.5f)*levelWidth, missileY, 0), Quaternion.identity) as GameObject;

		int baseIndex = Random.Range (0, cities.Length);

		go.transform.LookAt (cities[baseIndex].transform.position, Vector3.right);
		go.transform.Rotate (new Vector3(-90,0,-90));
		go.transform.Rotate (new Vector3(-90,0,0));
		SetSpeed(go);
		activeMissiles.Add (go);
	}

	void SetSpeed ( GameObject go ) {
		go.GetComponent<ConstantForce2D>().velocity = new Vector3(2 + 0.5f*level, 0, 0);
	}

	IEnumerator Victory () {
		victory.SetActive (true);
		yield return new WaitForSeconds (2);

		level++;
		Application.LoadLevel (Application.loadedLevel);
	}

}
