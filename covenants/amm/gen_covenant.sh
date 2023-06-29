gcc -E ./include/asset_covenant.h      | gawk '!/^#/' | sed 's/; require/;\n  require/g' > asset_covenant.cash
gcc -E ./include/lp_covenant.h         | gawk '!/^#/' | sed 's/; require/;\n  require/g' > lp_covenant.cash
gcc -E ./include/mint_lp_token.h       | gawk '!/^#/' | sed 's/; require/;\n  require/g' > mint_lp_token.cash
gcc -E ./include/burn_lp_token.h       | gawk '!/^#/' | sed 's/; require/;\n  require/g' > burn_lp_token.cash
gcc -E ./include/sell_token_to_pool.h  | gawk '!/^#/' | sed 's/; require/;\n  require/g' > sell_token_to_pool.cash
gcc -E ./include/buy_token_from_pool.h | gawk '!/^#/' | sed 's/; require/;\n  require/g' > buy_token_from_pool.cash
gcc -E ./include/withdraw_fee.h        | gawk '!/^#/' | sed 's/; require/;\n  require/g' > withdraw_fee.cash
