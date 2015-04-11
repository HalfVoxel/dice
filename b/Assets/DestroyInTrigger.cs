using UnityEngine;
using System.Collections;

public class DestroyInTrigger : MonoBehaviour {

	public void OnTriggerEnter2D (Collider2D coll) {
		GameObject.Destroy (coll.gameObject);
	}
}
