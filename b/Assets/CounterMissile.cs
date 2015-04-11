using UnityEngine;
using System.Collections;

public class CounterMissile : MonoBehaviour {

	public Vector3 target;

	public GameObject boom;

	// Update is called once per frame
	void Update () {
		if (Vector3.Dot (transform.position-target, transform.right) > 0) {
			GameObject.Instantiate (boom, target, Quaternion.identity);
			GameObject.Destroy (gameObject);
		}
	}
}
