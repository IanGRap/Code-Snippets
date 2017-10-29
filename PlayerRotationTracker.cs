// Ian Rapoport
// This AI program rotates the AI to be facing the character

using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerRotationTracker : MonoBehaviour {

	// default speed that the character rotates
	public float speed;
	// check that the program is active
	public bool active = true;

	// player transform to look at
	private Transform player;
	// current speed that the character is rotating
	private float currentSpeed;

	void Awake(){
		// set default values
		player = GameObject.FindGameObjectWithTag ("Player").transform;
		currentSpeed = speed;
		// assign function to listener for slowing down time
		EventManager.StopListening ("ChangeSpeed", ChangeSpeed);
		EventManager.StartListening ("ChangeSpeed", ChangeSpeed);
	}

	void Update () {
		// if the AI is active
		if (active) {
			// essentially the slop between the AI and the player
			Vector3 vectorToTarget = player.position - transform.position;
			// got this code from online. Essentially rotate toward the player with a smooth motion
			float angle = Mathf.Atan2(vectorToTarget.y, vectorToTarget.x) * Mathf.Rad2Deg - 90;
			Quaternion q = Quaternion.AngleAxis(angle, Vector3.forward);
			transform.rotation = Quaternion.Slerp(transform.rotation, q, Time.deltaTime * currentSpeed);
		}
	}

	// starts AI
	void SetActive(bool set){
		active = set;
	}

	// change the current rotation speed to be a percentage of the original
	public void ChangeSpeed(float percent){
		currentSpeed = speed * percent;
	}

	// remove function reference from listener to avoid leaks
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
