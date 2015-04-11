using UnityEngine;
using System.Collections;

public class DestroyAfter : MonoBehaviour {

	public float delay;

	// Use this for initialization
	IEnumerator Start () {
		yield return new WaitForSeconds (delay);
		GameObject.Destroy (gameObject);
	}
}
