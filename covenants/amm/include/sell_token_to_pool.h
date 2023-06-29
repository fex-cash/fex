pragma cashscript ^0.8.0;

#include "MULDIV.h"

contract SellTokenToPool() {
	function spend(int r) {
		VERSION();
		bytes category = tx.inputs[LP].tokenCategory;
		CHECK(r, category);
			
		int tokenAmount = tx.inputs[ASSET].tokenAmount;
		int newTokenAmount = CeilDiv(tokenAmount, r);
		int fee = (newTokenAmount-tokenAmount)/500;
		int newPoolTokenAmount = newTokenAmount + fee;
		require(tx.outputs[ASSET].tokenAmount == newPoolTokenAmount); //incr

		int bchValue = tx.inputs[ASSET].value;
		int newBchValue = CeilMul(bchValue, r);
		fee = (bchValue - newBchValue)/500;
		int newPoolBchValue = newBchValue + fee;
		require(tx.outputs[ASSET].value == newPoolBchValue); //decr

		int collectedFee = tx.inputs[LP].value;
		require(tx.outputs[LP].value == collectedFee + fee); //incr
		require(tx.outputs[LP].tokenAmount == tx.inputs[LP].tokenAmount); //equal
	}
}

