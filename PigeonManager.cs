// Ian Rapoport
// This program manages all the attack programs for the pigeon boss

using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PigeonManager : MonoBehaviour {

	// reference to each of the boss attack programs
	public PigeonRun run;
	public PigeonStrafe strafe;
	public PigeonHover hover;

	// an int to track which attack we are on
	private int current = 0;
	// are we currently moving or not
	private bool moveRight = false;

	// once on screen being attack
	void Init(){
		NextAttack ();
	}

	public void NextAttack(){
		// check which attack we are on
		if (current == 0) {
			run.Activate ();
		} else if (current == 1) {
			strafe.Activate (moveRight);
		} else {
			hover.Activate (moveRight);
		}

		// iterate to next attack
		current++;
		// change direction
		moveRight = !moveRight;
		// if we have gone through all the attacks start back at the begining
		if(current >= 3){
			current = 0;
		}
	}
}
