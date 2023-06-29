pragma cashscript ^0.8.0;

#include "MULDIV.h"

contract BuyTokenFromPool() {
	function spend(int r) {
		VERSION();
		bytes category = tx.inputs[LP].tokenCategory;
		CHECK(r, category);
			
		int tokenAmount = tx.inputs[ASSET].tokenAmount;
		int newTokenAmount = CeilMul(tokenAmount, r);
		int fee = (tokenAmount-newTokenAmount)/500;
		int newPoolTokenAmount = newTokenAmount + fee;
		require(tx.outputs[ASSET].tokenAmount == newPoolTokenAmount); //decr

		int bchValue = tx.inputs[ASSET].value;
		int newBchValue = CeilDiv(bchValue, r);
		fee = (newBchValue - bchValue)/500;
		int newPoolBchValue = newBchValue + fee;
		require(tx.outputs[ASSET].value == newPoolBchValue); //incr

		int collectedFee = tx.inputs[LP].value;
		require(tx.outputs[LP].value == collectedFee + fee); //incr
		require(tx.outputs[LP].tokenAmount == tx.inputs[LP].tokenAmount); //equal
	}
}

