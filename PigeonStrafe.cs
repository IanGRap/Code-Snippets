// Ian Rapoport
// The is the program for the strafe attack for the pigeon boss battle

using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PigeonStrafe : MonoBehaviour {

	// references to locations during movement
	public Transform upRight, upLeft, lowRight, lowLeft;
	// default movement speed
	public float speed;
	// references to different firing components for different directions
	public Shot_StraightLine leftMissile, leftSpread, rightMissile, rightSpread;
	// default fire rate and bullet speed
	public float fireRate;
	public float shotSpeed;

	private Rigidbody2D rb2d;
	// reference to the program the manages the different boss attacks
	private PigeonManager manager;
	// refernce to if we are moving and which direction we are moving
	private bool active = false, movingRight;
	// our current speeds and timers
	private float currentSpeed;
	private bool fireMissile;
	private float timeTillNextFire;
	private float currentFireRate;
	// for bullet speeds
	private Transform bulletPool;

	void Awake(){
		// assign function for slow down time listener
		EventManager.StopListening ("ChangeSpeed", ChangeSpeed);
		EventManager.StartListening ("ChangeSpeed", ChangeSpeed);

		// assign default values and references
		rb2d = GetComponent <Rigidbody2D> ();
		manager = GetComponentInParent <PigeonManager> ();
		currentSpeed = speed;
		bulletPool = GameObject.FindGameObjectWithTag ("Bullet Pool").transform;
		currentFireRate = fireRate;
	}
	
	// Update is called once per frame
	void Update () {
		// if this attack is happening
		if (active) {
			// what direction are we moving
			if (movingRight) {
				//have we passed our destination point?
				if (transform.position.x >= lowRight.position.x) {
					// stop attack and move to next
					active = false;
					manager.NextAttack ();
				}
			} else {
				if (transform.position.x <= lowLeft.position.x) {
					active = false;
					manager.NextAttack ();
				}
			}

			// decrement time till next shot fired
			timeTillNextFire -= Time.deltaTime;
			if (timeTillNextFire <= 0) {
				Fire ();
			}
		}
	}

	void FixedUpdate(){
		// if the attack is in progress
		if (active) {
			// the direction we will be moving
			Vector2 direction;
			// 3d representation of our current location compared to our destination
			Vector3 vectorToTarget;
			// check our direction
			if (movingRight) {
				// set our direction to be based off the destination normalized
				direction = new Vector2 (lowRight.position.x - transform.position.x, lowRight.position.y - transform.position.y).normalized;
				// basically find the slop between us and and the destination
				vectorToTarget = lowRight.position - transform.position;
			} else {
				direction = new Vector2 (lowLeft.position.x - transform.position.x,  lowLeft.position.y - transform.position.y).normalized;
				vectorToTarget = lowLeft.position - transform.position;
			}

			// I got this code from online. Essentially the direction the plane is facing is being constantly updated so it is looking at the destination
			float angle = Mathf.Atan2(vectorToTarget.y, vectorToTarget.x) * Mathf.Rad2Deg + 90;
			Quaternion q = Quaternion.AngleAxis(angle, Vector3.forward);
			transform.localRotation = q;
			// set our speed based on current speed
			rb2d.velocity = direction * currentSpeed;
		}
	}

	// called by manager to start attack
	public void Activate(bool moveTowardsRight){
		set variables
		active = true;
		movingRight = moveTowardsRight;
		//set our destination based on direction we are moving
		if (movingRight) {
			transform.position = upLeft.position;
		} else {
			transform.position = upRight.position;
		}
		// reset values
		timeTillNextFire = currentFireRate;
	}

	// called when a projectile is fired
	void Fire(){
		// check direction
		if (movingRight) {
			// check which alternating projectile to fire
			if (fireMissile) {
				// call firing component
				rightMissile.Shoot (Vector3.down, shotSpeed, false);
			} else {
				rightSpread.Shoot (Vector3.down, shotSpeed, false);
			}
		} else {
			if (fireMissile) {
				leftMissile.Shoot (Vector3.down, shotSpeed, false);
			} else {
				leftSpread.Shoot (Vector3.down, shotSpeed, false);
			}
		}
		// reset values
		timeTillNextFire = currentFireRate;
		// switch projectile type
		fireMissile = !fireMissile;
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
		
	// remove function from listener to avoid data leaks
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
