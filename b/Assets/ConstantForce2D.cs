using UnityEngine;
using System.Collections;

public class ConstantForce2D : MonoBehaviour {

	public Vector3 velocity;
	
	// Update is called once per frame
	void Update () {
		GetComponent<Rigidbody2D>().velocity = transform.TransformDirection (velocity);
	}
}
