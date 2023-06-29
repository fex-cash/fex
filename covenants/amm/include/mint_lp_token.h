pragma cashscript ^0.8.0;

#include "MULDIV.h"

contract MintLpToken() {
	function spend(int r) {
		VERSION();
		bytes category = tx.inputs[LP].tokenCategory;
		CHECK(r, category);

		int tokenAmount = tx.inputs[ASSET].tokenAmount;
		int newTokenAmount = CeilDiv(tokenAmount, r);
		require(tx.outputs[ASSET].tokenAmount == newTokenAmount); //incr

		int bchValue = tx.inputs[ASSET].value;
		int newBchValue = CeilDiv(bchValue, r);
		require(tx.outputs[ASSET].value == newBchValue); //incr

		int lpTokenSupply = MAX_SUPPLY - tx.inputs[LP].tokenAmount;
		int newLpTokenSupply = FloorDiv(lpTokenSupply, r); 
		require(MAX_SUPPLY - tx.outputs[LP].tokenAmount == newLpTokenSupply); //incr

		int collectedFee = tx.inputs[LP].value;
		require(tx.outputs[LP].value == collectedFee); //equal
	}
}

