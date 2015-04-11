using UnityEngine;
using System.Collections;

public class Ship : MonoBehaviour {

	public Vector3 velocity;
	public float yspeed;

	public GameObject bullet;

	GameObject lastBullet;

	float lastFire = 0;
	// Use this for initialization
	void Start () {
	
	}

	public void Update () {
		Vector3 p = transform.position + velocity*Time.deltaTime + yspeed*Vector3.up*Input.GetAxis("Vertical")*Time.deltaTime;

		GetComponent<Rigidbody2D>().MovePosition (p);

		if (Input.GetKey(KeyCode.Space) && Time.time - lastFire > 0.5f && !lastBullet) {
			lastFire = Time.time;
			lastBullet = GameObject.Instantiate (bullet, transform.position, transform.rotation) as GameObject;
		}
	}

	// Update is called once per frame
	void OnCollisionEnter2D ( Collision2D other) {
		Debug.Break();
		Debug.LogError ("Game Over");
	}
}
