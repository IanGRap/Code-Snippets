// Ian Rapoport
// This program controls AI that is supposed to move towards the player and then follow them. This is used primarily for the wingmen allies

using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MoveToPlayer : MonoBehaviour {

	// this is how far away the AI should be from the player while following them
	public Vector2 offset;
	// the speed at which the AI moves to the player
	public float speed;
	// tracks whether or not the AI has arrived at the player and begun tailing them
	public bool arrived;

	// this tracks whethr or not the AI is moving towards the player or currently following them
	private bool movingToPlayer;
	// the player trasform to follow
	private Transform player;
	// the start and return location
	private Vector3 start;
	// whether or not the AI is currently moving
	private bool active;
	// reference to the physical body
	private Rigidbody2D rb2d;

	//assign important variables once game has begun
	void Awake(){
		start = transform.position;
		rb2d = GetComponent <Rigidbody2D> ();
	}

	// called when the AI begins moving or needs to stop
	public void ActivateMoveTo(){
		//check it AI is moving, if isn't, set it too
		if (!active) {
			// find the destination then set variables for moving toward
			player = GameObject.FindGameObjectWithTag ("Player").transform;
			active = true;
            arrived = false;
			movingToPlayer = true;
		// if the AI is currently moving set it to return
		} else {
			movingToPlayer = false;
		}
	}

	void FixedUpdate(){
		//If the character is supposed to be moving, move it
		if (active) {
			MoveTowards ();
		}
	}

	void MoveTowards(){
		//reference for when the AI needs to be in this fram
		Vector3 target;
		// check whether or not we need set the target to move as the player or return to start
		if (movingToPlayer) {
			target = new Vector3 (player.position.x + offset.x, player.position.y + offset.y, 0);
		} else{
			target = start;
		}
		// if we are within 1 measurement of the player
		if (Mathf.Abs (transform.position.x - target.x) < 1 || Mathf.Abs (transform.position.y - target.y) < 1) {
			// set our position to be the target position and stop velocity to keep us in the target position
			transform.position = target;
			rb2d.velocity = new Vector2 (0f, 0f);
			// if we havent set to true, do so
			if (movingToPlayer && !arrived) {
				arrived = true;
			// if we have returned to start, stop moving
			} else if(!movingToPlayer){
				active = false;
			}
		// we are moving toward the target but have not yet gotten close
		} else {
			// create a vector 2 towards our target
			float x = target.x - transform.position.x;
			float y = target.y - transform.position.y;
			Vector2 path = new Vector2 (x, y).normalized;
			// set our velocity to send us toward our target
			rb2d.velocity = path * speed;
		}
	}
}
