pragma cashscript ^0.8.0;

#include "MULDIV.h"

contract LpCovenant() {
	function spend() {
		VERSION();
		require(this.activeInputIndex == LP);
		bytes category = tx.inputs[LP].tokenCategory;

		// I am lp_covenant
		require(tx.outputs[LP].lockingBytecode == tx.inputs[LP].lockingBytecode);
		require(tx.outputs[LP].nftCommitment == tx.inputs[LP].nftCommitment);
		require(tx.outputs[LP].tokenCategory == category);
		
		// the lp_covenant and the func_covenant are bound together
		require(tx.inputs[FUNC].tokenCategory == category);
		int commitment = int(tx.inputs[FUNC].nftCommitment);
		require(1 <= commitment && commitment <= 5);
		
		// the lp_covenant and the asset_covenant are bound together (always spent together)
		require(tx.inputs[LP].outpointTransactionHash == tx.inputs[ASSET].outpointTransactionHash);
    require(tx.inputs[LP].outpointIndex == LP);
    require(tx.inputs[ASSET].outpointIndex == ASSET);
	}
}


