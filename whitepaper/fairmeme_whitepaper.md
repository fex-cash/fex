## Fair Meme: A fair approach to launch tokens on Bitcoin Cash

### Background

Recently, due to the boom in the Ordinals and BRC20 protocols, inscription tokens have been in play on various blockchains.
Although these inscription tokens are purported to be fair launching, due to the "gas war" or some people using hacking tactics,
it has made it very difficult for most investors to actually mint the inscription tokens on offer. And even if they do minting successfully, they have to pay a large amount of fee to miners.

While most inscription tokens on other pow blockchains can only be traded as bulk orders, Fex.Cash has previously introduced an AMM Swap feature based on CashTokens, which makes for a better trading experience in comparison.
Fair Meme is a new approach for the fair launching of CashTokens, which was introduced by Fex.Cash after combining experience with AMM features.

### Features

Fair Meme has the following features:

1. Issue of Fair Meme tokens: Anyone can create a new Fair Meme token and specify the price when it will be fairly launched.
2. Fair Launch: After the start time, if the sold amount has not yet reached half of the total supply, everyone can buy Fair Meme tokens at the same price, and the collected BCH will be temporarily stored in the smart contract.
3. Create AMM Pool: When the sold amount has reached half of the total supply, or the end time has been reached, anyone can trigger the creation of the AMM pool, the smart contract will put the collected BCH and the same amount of Fair Meme tokens as the sold tokens into the AMM pool. The corresponding LP tokens minted in this step will be stored in the smart contract and used as the reward of the `Earn Fair Meme` part.
4. Earn Fair Meme: Users can mint LP tokens using Fair Meme tokens and BCH. If they lock their LP tokens for a period of time, they can receive a certain amount of LP token rewards when unlocking. That means they can receive interests by locking the LP tokens.

As you can see from the above features, it is fair for anyone, and everyone can decide how much to buy according to their own situation, without having to pay a high miner fee or clicking multiple times like other inscription tokens.

The token issuer operates exactly the same as the other users except for creating Fair Meme tokens, and the collected BCH by Fair Launch is subsequently deposited into the AMM Pool to provide liquidity for trading.

Providing BCH and Fair Meme tokens for liquidity brings transaction fee rewards along with impermanent loss, and in order to encourage users to hold LP tokens for a long period of time, Fair Meme will distribute rewards to users who are willing to provide LP for a long period of time.

Fair Meme is an innovative mechanism that combines fair launch and AMM to ensure fairness and provide a better user experience.


### Details

#### Issue of Fair Meme tokens

1. First of all, a user need to create a CRC20 token, after creating it, its total supply will all enter the current user's account.
   (Recommended value: total supply is 21000000, decimals is 8)
2. The following parameters need to be set for issuing Fair Meme:
    - Token: Select the token which becomes Fair Meme.
    - Fair Launch Price: How much BCH per token.
    - Start Time/Start Block: Users can only start buying from the smart contract when the start block height has been reached.
    - End Time/End Block: The creation of an AMM pool is triggered when the sold amount reaches half of the total supply or the current block height reaches the end block height.
    - APY: Annualized Percentage Rate (APY) that a user can earn after locking liquidity for a period.
      (Recommended value: 5~50%)
      (Note that currently a locking period is 4032 block intervals, approximately 4 weeks)
3. The final total supply of Fair Meme tokens consists of two equal parts:
    - The sold amount during the `Fair Launch` phase.
    - The amount which is added as liquidity together with BCH, when the AMM Pool is created.

#### Fair Launch

1. Fair Launch will start after the start block height and will end when the sold amount reaches half of the total supply.
2. The amount of each sell is arbitrary, as long as the total number of sold tokens does not reach half. However, it is not recommended that the amount is too small, the smart contract will collect at least 0.001 BCH each time, so theoretically the minimum amount of each sell is `0.001/price`.
3. The collected BCH will be temporarily stored in the smart contract, these BCH will be put into the AMM Pool later, Fex.Cash and the token issuer will not collect fees from it.

#### Create AMM Pool

1. Anyone can trigger the creation of AMM pool after the sold amount has reached half or the end time has been reached.
   At this point, two situations will be encountered:
    - If the sold amount has reached half, the pool will be created with all the BCH collected and the other half of the tokens left in the contract.
    - If the sold amount has not reached half but has reached the end block height, the pool will be created with the BCH collected and the same amount of tokens as sold, while the remaining tokens will be burnt.
2. After creating AMM Pool, the smart contract will use the all LP tokens it owned to reward the LP token lockers.

#### Earn Fair Meme tokens and BCH

1. Users can lock LP tokens of Fair Meme for approximately 4 weeks (4032 blocks), and they will be rewarded with a certain amount of LP tokens upon expiration.

2. After a locking period, users can get approximately `((1+APY)**(1.0/365))**28` times the locked LP tokens.

3. The rewarded LP tokens can be burnt to get Fair Meme tokens and BCH.

### Conclusion

This Fair Meme approach is fair because:

1. The first half of tokens are issued at the same price for everyone.
2. After creating the AMM Pool, if the supply and demand for tokens are balanced, i.e. some people want to buy and some people want to sell, and they demand the same amount, then the price will continue to stay the same.
3. The users who buy Fair Meme during Fair Launch is not ensured to get a better price than the others who buy them from the AMM pool later. Only if the buying of tokens is greater than the selling of tokens after the AMM pool is established, then early participants can make a profit.

Last, we would like to thank our community for their genius ideas, Fair Meme is inspired by you.
