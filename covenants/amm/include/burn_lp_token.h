pragma cashscript ^0.8.0;

#include "MULDIV.h"

contract BurnLpToken() {
	function spend(int r) {
		VERSION();
		bytes category = tx.inputs[LP].tokenCategory;
		CHECK(r, category);
		
		int tokenAmount = tx.inputs[ASSET].tokenAmount;
		int newTokenAmount = CeilMul(tokenAmount, r);
		require(tx.outputs[ASSET].tokenAmount == newTokenAmount); //decr

		int bchValue = tx.inputs[ASSET].value;
		int newBchValue = CeilMul(bchValue, r);
		require(tx.outputs[ASSET].value == newBchValue); //decr

		int lpTokenSupply = MAX_SUPPLY - tx.inputs[LP].tokenAmount;
		int newLpTokenSupply = FloorMul(lpTokenSupply, r); 
		require(MAX_SUPPLY - tx.outputs[LP].tokenAmount == newLpTokenSupply); //decr

		int collectedFee = tx.inputs[LP].value;
		require(tx.outputs[LP].value == collectedFee); //equal
	}
}

