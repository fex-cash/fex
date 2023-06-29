pragma cashscript ^0.8.0;

#include "MULDIV.h"

contract WithdrawFee(bytes20 pubkeyHash) {
	function spend(/*sig sig, pubkey pbk, */bytes20 newHash) {
		VERSION();
		bytes category = tx.inputs[LP].tokenCategory;
		BASIC_CHECK(category);

		// require(hash160(pbk) == pubkeyHash);
		// require(checkSig(sig, pbk));
		bytes25 feeToLock = new LockingBytecodeP2PKH(pubkeyHash);
		require(tx.inputs[3].lockingBytecode == feeToLock);

		require(tx.outputs[ASSET].tokenAmount == tx.inputs[ASSET].tokenAmount);
		require(tx.outputs[ASSET].value == tx.inputs[ASSET].value);
		require(tx.outputs[LP].tokenAmount == tx.inputs[LP].tokenAmount);

		bytes newContract = 0x14 + newHash + this.activeBytecode.split(21)[1];
		bytes23 newContractLock = new LockingBytecodeP2SH20(hash160(newContract));
		require(tx.outputs[FUNC].lockingBytecode == newContractLock);
	}
}


