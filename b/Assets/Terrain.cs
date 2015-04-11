using UnityEngine;
using System.Collections;

public class Terrain : MonoBehaviour {

	public LineRenderer rend;

	public Vector3 scale;
	public Vector3 perlin;
	public int points;

	Vector2[] pts;
	public GameObject prefab;

	public Transform player;

	void Start () {
		pts = new Vector2[50];
	}

	// Use this for initialization
	void Update () {

		if (player.position.x > pts[pts.Length-3].x*0.5f) {
			points *= 2;


			pts = new Vector2[points+2];

			var poly = GetComponent<PolygonCollider2D>();

			rend.SetVertexCount (points);

			for (int i = 0; i < points; i++) {
				Vector3 p = new Vector3(i, Mathf.PerlinNoise(i*perlin.x,perlin.y), 0);
				p.Scale (scale);
				rend.SetPosition (i, p);
				pts[i] = p;
			}

			pts[pts.Length-2] = pts[pts.Length-3] - Vector2.up*10;
			pts[pts.Length-1] = pts[0] - Vector2.up*10;

			poly.points = pts;
		}

		if (Random.value < 0.1f) {
			int index = Random.Range(0, pts.Length);
			GameObject.Instantiate (prefab, pts[index], Quaternion.identity);
		}
	}
}
