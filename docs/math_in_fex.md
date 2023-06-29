## Math In Fex

#### Variable Definition

```
// 2^30 is almost one billion
let TwoExp30 = 1073741824
```

#### Purpose of Calculation

1. Given `r ∈ [0, TwoExp30)`.
2. If we want to calculate `a * r / TwoExp30`, the expression`a * r` is likely to overflow，but `(a/TwoExp30) * r` and `(a%TwoExp30) * r` are not overflow.
3. If we want to calculate `a * TwoExp30 / r`， the expression `a * TwoExp30` is likely to overflow, but `(a/r) * TwoExp30` and `(a%r) * TwoExp30` are not overflow.

#### Derivation

```
a * (x/y) = (floor(a/y) * y + (a%y)) * (x/y)
          = (floor(a/y) * y * (x/y) + (a%y) * (x/y)
          = (floor(a/y) * x + (a%y) * x / y
```

If `x = r, y = TwoExp30`, then:
`a * r / TwoExp30 = floor(a/TwoExp30) * r + (a%TwoExp30) * r / TwoExp30`

If `x = TwoExp30, y = r`, then:
`a * TwoExp30 / r = floor(a/r) * TwoExp30  + (a%r) * TwoExp30 / r`

#### Usage in Fex

According to UniswapV2, when users add liquidity in AMM, we have the following formula:

```
newLpTokenSupply  = lpTokenSupply * (totalTokenInPool+userInputToken) / totalTokenInPool
```

Then:

```
newLpTokenSupply = lpTokenSupply / ( totalTokenInPool / (totalTokenInPool+userInputToken) )
```

`newLpTokenSupply` is the total supply of LP tokens in the pool after users add liquidity.

Let `totalTokenInPool / (totalTokenInPool+userInputToken) = r / TwoExp30`, and apply the formula we derived above,
we can obtain the following calculation code in `mint_lp_token.cash`:

```
int newLpTokenSupply = (((lpTokenSupply/r)*1073741824) + ((lpTokenSupply%r)*1073741824)/r);
```

Similarly, when users burn liquidity, there is the code in `burn_lp_token.cash`:
```
int newLpTokenSupply = ((lpTokenSupply/1073741824)*r + ((lpTokenSupply%1073741824)*r)/1073741824);
```

Likewise, when users buy or sell tokens, the code is: 
```
// sell_token_to_pool.cash
int newTokenAmount = (((tokenAmount/r)*1073741824) + ((tokenAmount%r)*1073741824 + r - 1)/r);

// buy_token_to_pool.cash
int newTokenAmount = ((tokenAmount/1073741824)*r + ((tokenAmount%1073741824)*r + 1073741823)/1073741824);
```

The last term `(r - 1) / r` is used to round the result upwards.
