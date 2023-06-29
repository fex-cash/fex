#define FUNC 0
#define LP 1
#define ASSET 2
#define MAX_SUPPLY 4503599627370496
#define DENOMINATOR 1073741824
#define DENOMINATORMinus1 1073741823
#define FloorMul(a, r) ((a/DENOMINATOR)*r + ((a%DENOMINATOR)*r)/DENOMINATOR)
#define FloorDiv(a, r) (((a/r)*DENOMINATOR) + ((a%r)*DENOMINATOR)/r)
#define CeilMul(a, r) ((a/DENOMINATOR)*r + ((a%DENOMINATOR)*r + DENOMINATORMinus1)/DENOMINATOR)
#define CeilDiv(a, r) (((a/r)*DENOMINATOR) + ((a%r)*DENOMINATOR + r - 1)/r)


#define BASIC_CHECK(category) require(this.activeInputIndex == FUNC);\
                              require(tx.outputs[FUNC].lockingBytecode == tx.inputs[FUNC].lockingBytecode);\
                              require(tx.outputs[FUNC].nftCommitment == tx.inputs[FUNC].nftCommitment);\
                              require(tx.outputs[FUNC].tokenCategory == category);\
                              require(int(tx.inputs[LP].nftCommitment) == 0)

#define CHECK(r, category) require(r < DENOMINATOR);\
                           BASIC_CHECK(category)

#define VERSION() int constant version = 1;\
                   require(version > 0)