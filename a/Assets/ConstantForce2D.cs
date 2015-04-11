using UnityEngine;
using System.Collections;

public class ConstantForce2D : MonoBehaviour {

	public Vector2 force;

	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
		GetComponent<Rigidbody2D>().AddForce (force);
	}
}
