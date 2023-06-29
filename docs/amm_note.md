## AMM Note
The transaction that initializes the Amm Pool is also the Genesis Transaction that mints the liquidity token.  It has a total of 8 outputs, 6 of which are NFTs with `minting=false` and `mutable=false`. The following describes these 8 outputs in detail:

0. CategoryCovenant, which is a P2PKH output where the "public key" is actually the traded token's category.

1. LpCovenant, which holds the liquidity tokens that have not yet been distributed, and the fees collected for project owner, with `nftCommitment=0`

2. AssetCovenant, which holds two tokens in the AMM Pool, one must be BCH

3. MintLpToken, which is responsible for increasing liquidity, with `nftCommitment=1`

4. BurnLpToken, which is responsible for burning liquidity, with `nftCommitment=2`

5. BuyTokenFromPool, through which user spends BCH to buy token from the pool, with `nftCommitment=3`

6. SellTokenToPool, through which user sells the token to the pool to get the BCH, with `nftCommitment=4`

7. WithdrawFee, which the project owner can extract the accumulated fee in LpCovenant, with `nftCommitment=5`

The last 5 NFTs are also named as Function NFTs, which are just used to implement the functions in a smart contract and are not holding tokens.

We think this splitting of code logic into multiple covenants will be a common practice in the future, since BCH currently has many limitations on scripts.

For more information, you can read: https://bitcoincashresearch.org/t/raising-the-520-byte-push-limit-201-operation-limit/282

```
MAX_SCRIPT_ELEMENT_SIZE = 520;
MAX_OPS_PER_SCRIPT = 201;
```

The internal logic of these 5 NFTs ensures the following two characteristics:

1. Self-Preservation. Being spent and then immediately created again, while keeping the code content, tokenCategory and nftCommitment unchanged:

For asset-covenant, its `lockingBytecode`/`tokenCategory` needs to remain unchanged, it does not have the nftCommitment attribute.

For lp-covenant, its `lockingBytecode`/`tokenCategory`/`nftCommitment` needs to remain unchanged.

For func-covenants, theirs `lockingBytecode`/`tokenCategory`/`nftCommitment` need to remain unchanged.

In each AMM transaction, the 0th input and output must be one of the Functional NFTs, the 1st input and output must be an LpCovenant, and the 2nd input and output must be an AssetCovenant.

2. InterLocking. They must be used as inputs with each other simultaneously:

For lp-covenant and asset-covenant, they interlock via `outpointTransactionHash`.

For lp-covenant and func-covenants, they interlock via `tokenCategory`/`nftCommitment`.

The logic of Functional NFT is responsible for spending the existing LpCovenant and AssetCovenant and creating new LpCovenant and AssetCovenant.

In Genesis transaction, the assets assigned to the lp-covenant and asset-covenant are subject to:
```
LpCovenant.tokenAmount == (2**52) - BURNT_LP_TOKEN 
BURNT_LP_TOKEN * BURNT_LP_TOKEN <= AssetCovenant.bchValue * AssetCovenant.tokenAmount < (BURNT_LP_TOKEN+1) * (BURNT_LP_TOKEN+1)
```

**Note:**

All covenants have no `minting` and `mutable` properties.

To avoid inaccuracy, the number of liquidity tokens should be burned off at least 1e6 during initialization (the same effect as UniswapV2's `MINIMUM_LIQUIDITY` given to the zero address taking the value 1e6), requiring `BURNT_LP_TOKEN == 1e6`.  This part of the burned off LP Tokens is equivalent to being distributed to a zero-address.

The number of LP Tokens that have been distributed will be calculated as `(2**52) - LpCovenant.tokenAmount` subsequently.

For Genesis Transaction of Amm Pool, if the 8 outputs are not created properly, like `bchValue`/`tokenCategory`/`nftCommitment`/`tokenAmount` do not meet the specification, then the front-end cannot recognize the pool and will not show it to the user.

The covenants cannot do 256-bit multiplication and division due to the 64-bit limitation of integers in the BCH script. It is also difficult to use 64-bit integers to make 128-bit or 256-bit operations within a limited number of bytes and without subroutine support.

A possible expedient is to define a special multiplication and division method by multiplying or dividing by a rational number `R` in the interval `[0,1)`. This rational number `R` is represented by an integer `r` in the interval `[0, 2^30)`, and multiplication by r and division by r can be defined as:

```
MASK = (1<<30)-1;
x * R = (x>>30)*r + (((x&MASK)*r)>>30);
x / R = ((x/r)<<30) + ((x%r)<<30)/r;
```

The above calculations will not overflow in any step if the number of all coins does not exceed 2^52.

If users provide an illegal value that causes an overflow in any calculation step, the BCH script will simply **FAIL**.

