// Ian Rapoport
// This program runs the hover attack for the Pigeon boss battle

using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PigeonHover : MonoBehaviour {

	// These locations dictate the various areas the boss moves to and from during his attacks
	public Transform outRight, inRight, outLeft, inLeft;
	// These are the two different projectiles and their firing components for the boss
	public Shot_StraightLine missile, spread;
	// default speeds of boss
	public float speed;
	public float fireRate;
	public float shotSpeed;

	private Rigidbody2D rb2d;
	// manager of all boss programs
	private PigeonManager manager;
	// bools to track where the boss is moving and if it is moving
	private bool active = false, pivoted = false, movingRight;
	// current speeds accounting for time being slowed down
	private float currentSpeed;
	private float timeTillNextFire;
	private float currentFireRate;
	// tracks which type of projectile is being shot
	private bool fireMissile;
	// reference for tracking all bullets on screen
	private Transform bulletpool;

	void Awake(){
		//assign change speed function to the listener that controls slowing down time
		EventManager.StopListening ("ChangeSpeed", ChangeSpeed);
		EventManager.StartListening ("ChangeSpeed", ChangeSpeed);

		//assign default values
		rb2d = GetComponent <Rigidbody2D> ();
		manager = GetComponentInParent <PigeonManager> ();
		currentSpeed = speed;
		currentFireRate = fireRate;
		bulletpool = GameObject.FindGameObjectWithTag ("Bullet Pool").transform;
	}

	void FixedUpdate(){
		// if this attack is currently being used
		if (active) {
			// check which direction we move since it goes back and forth
			if (movingRight) {
				// set our velocity in a dirction based on our current speed
				rb2d.velocity = Vector2.right * currentSpeed;
			} else {
				rb2d.velocity = -Vector2.right * currentSpeed;
			}
		}
	}
	
	// Update is called once per frame
	void Update () {
		// if we are moving
		if (active) {
			// check our direction
			if (movingRight) {
				// check if we have passed the pivot point and need to reverse direction
				if (pivoted) {
					// if we have passed the finish poin
					if (transform.position.x > outRight.position.x) {
						// reset variables
						active = false;
						pivoted = false;
						// tell the manager to start the next attack
						manager.NextAttack ();
					}
				} else {
					// check if we have reached the pivot point
					if(transform.position.x > inRight.position.x){
						// set pivot to true and change direction variable
						pivoted = true;
						movingRight = false;
					}
				}
			} else {
				if (pivoted) {
					if (transform.position.x < outLeft.position.x) {
						active = false;
						pivoted = false;
						manager.NextAttack ();
					}
				} else {
					if(transform.position.x < inLeft.position.x){
						pivoted = true;
						movingRight = true;
					}
				}
			}

			// decrement the timer till the next time a projectile should be fired
			timeTillNextFire -= Time.deltaTime;
			// check if it is time to fire a bullet
			if (timeTillNextFire <= 0) {
				Fire ();
			}
		}
	}

	// called by manager to activate attack, takes in the dirction we start and move towards
	public void Activate(bool moveTowardsRight){
		// reset variables
		timeTillNextFire = currentFireRate;
		active = true;
		pivoted = false;
		movingRight = moveTowardsRight;
		// set out starting location based on direction we will be moving
		if (movingRight) {
			transform.position = outLeft.position;
		} else {
			transform.position = outRight.position;
		}
		// reset our rotation
		transform.localRotation = Quaternion.identity;
	}

	void Fire(){
		// check what projectile we are firing, then call the firing component
		if (fireMissile) {
			missile.Shoot (Vector3.down, shotSpeed, false);
		} else {
			spread.Shoot (Vector3.down, shotSpeed, false);
		}
		// switch the projectile to fire for next attack
		fireMissile = !fireMissile;
		// reset timer till next shot
		timeTillNextFire = currentFireRate;
	}

	// change the speeds and times remaing for attacks and movements based on slowing time
	// this formual was orignally derived by my teammate Jarret van den Berg
	// percent is what percent of our original speed we will be moving
	public void ChangeSpeed(float percent){
		// get a ratio of how much time we have remaining until the next attack
		float ratio = timeTillNextFire / currentFireRate;
		// set time of fire rate based on percent, so if percent is 0.5 then our fire rate gets doubled
		currentFireRate = fireRate * (1f / percent);
		// set the remaining time till we fire again as whatever percent we originally had remaining
		timeTillNextFire = currentFireRate * ratio;

		//set our speed as a percentage of the orignal
		currentSpeed = speed * percent;
	}

	// remove functions from listener to avoid memory leaks
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
