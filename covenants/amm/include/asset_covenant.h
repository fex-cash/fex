pragma cashscript ^0.8.0;

#include "MULDIV.h"

contract AssetCovenant() {
	function spend() {
		VERSION();
		// I am asset_covenant
		require(this.activeInputIndex == ASSET);
		require(tx.outputs[ASSET].lockingBytecode == tx.inputs[ASSET].lockingBytecode);
		require(tx.outputs[ASSET].tokenCategory == tx.inputs[ASSET].tokenCategory);
		
		// the lp_covenant and the asset_covenant are binded together (always spent together)
		require(tx.inputs[LP].outpointTransactionHash== tx.inputs[ASSET].outpointTransactionHash);
	}
}



