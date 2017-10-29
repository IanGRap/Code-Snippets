// Ian Rapoport
// This is the program for the run movement for the pigeon boss battle

using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PigeonRun : MonoBehaviour {

	// reference to start (top) and stop (bottom) positions
	public Transform top, bottom;
	// default speed
	public float speed;

	// refence to if we are moving
	private bool active;
	// adjusted speed with time change
	private float currentSpeed;
	private Rigidbody2D rb2d;
	// reference to program that manages boss
	private PigeonManager manager;

	void Awake(){
		// set change speed function to listner
		EventManager.StopListening ("ChangeSpeed", ChangeSpeed);
		EventManager.StartListening ("ChangeSpeed", ChangeSpeed);

		// assign default values
		rb2d = GetComponent <Rigidbody2D> ();
		manager = GetComponentInParent <PigeonManager> ();
		currentSpeed = speed;
	}

	void FixedUpdate(){
		// if we are moving
		if (active) {
			// set our velocity based on our current speed downward
			rb2d.velocity = -Vector2.up * currentSpeed;
		}
	}
	
	// Update is called once per frame
	void Update () {
		if (active) {
			// if we have passed the end point
			if (transform.position.y < bottom.position.y) {
				// end attack and move to next one
				active = false;
				manager.NextAttack ();
			}
		}
	}

	// called when attack is activated
	public void Activate(){
		//reset all values and go to start position
		active = true;
		transform.position = top.position;
		transform.localRotation = Quaternion.identity;
	}

	// change the speed based on time slowing down
	public void ChangeSpeed(float percent){
		//set our speed as a percentage of the orignal
		currentSpeed = speed * percent;
	}

	// remove function reference from listener to avoid data leaks
	void OnApplicationQuit(){
		EventManager.StopListening ("ChangeSpeed", ChangeSpeed);
	}

	void OnDestroy(){
		EventManager.StopListening ("ChangeSpeed", ChangeSpeed);
	}

	void OnDisable(){
		EventManager.StopListening ("ChangeSpeed", ChangeSpeed);
	}
}
