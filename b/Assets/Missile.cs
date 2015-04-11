using UnityEngine;
using System.Collections;

public class Missile : MonoBehaviour {

	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {

	}

	public void OnCollisionEnter2D (Collision2D coll) {
		if (coll.gameObject.name != "Terrain") {
			GameObject.Destroy (gameObject);
			GameObject.Destroy (coll.gameObject);
		}
	}
}
