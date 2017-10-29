// Ian Rapoport
// This is a VERY basic AI script used for moving enemies in the bullet hell game

using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class LinearMovement : MonoBehaviour {

	// reference to the default speed of the character. We need to keep track of this for when time is slowed down then returned to normal
	public float speed;

	// refernces to the physical body of the character
	private Rigidbody2D rb2d;
	// the speed at which the character is currently moving. This changes when time is slowed down.
	private float currentSpeed;

	void Awake(){
		// assign the change speed function to the manager that controls time being slow down
		EventManager.StopListening ("ChangeSpeed", ChangeSpeed);
		EventManager.StartListening ("ChangeSpeed", ChangeSpeed);
	}

	// this is called once the character arrives on screen
	void Init(){
		// begin moving the character
		StartCoroutine ("Move");
	}

	// changes the speed of the character when time slows down and speeds up
	void ChangeSpeed(float p){
		// set the current speed to be a percentage of the original. For example, p=1 sets the speed back to its original and p=0.5 sets the speed to half time
		currentSpeed = speed * p;
	}

	// the basic function that moves the character, called by init
	IEnumerator Move(){
		// set speed to normal at the begining
		ChangeSpeed (1);
		// move the character down the screen while active
		while (true) {
			transform.position -= transform.up * currentSpeed * Time.deltaTime * 50;
			yield return null;
		}
	}

	// these functions remove the change speed function from the listener to avoid data leaks
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
