pragma cashscript ^0.8.0;

#include "MULDIV.h"

contract AssetCovenant(bytes32 lpCategory) {
	function spend() {
		VERSION();
		// I am asset_covenant
		require(this.activeInputIndex == ASSET);
		require(tx.outputs[ASSET].lockingBytecode == tx.inputs[ASSET].lockingBytecode);
		require(tx.outputs[ASSET].tokenCategory == tx.inputs[ASSET].tokenCategory);

		// the asset_covenant and the func_covenant are bound together
		require(tx.inputs[FUNC].tokenCategory == lpCategory);
		require(tx.inputs[LP].tokenCategory == lpCategory);
		int commitment = int(tx.inputs[FUNC].nftCommitment);
		require(1 <= commitment && commitment <= 5);

		// the lp_covenant and the asset_covenant are bound together (always spent together)
		require(tx.inputs[LP].outpointTransactionHash == tx.inputs[ASSET].outpointTransactionHash);
		require(tx.inputs[LP].outpointIndex == LP);
    	require(tx.inputs[ASSET].outpointIndex == ASSET);
	}
}



