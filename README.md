question 10

We are making an action game (2D/3D is irrelevant).
In game we need to make coins appear when the player destroys enemies or objects.
Please implement an object pool so that we don't have to allocate those coins all the time. 
In this question we are only interested in the pool logic (api and implementation) so there is no need to worry about details such as rendering and effects. The implementation is up to you but please try to fulfill at least those conditions:

 - 10000 coins are allocated at init time
 - no allocation happens after that during the game
 - coins disapears when the player takes them
 - coins disappears after 300 frame

class Coin
{
}
	
class CoinObjectPool
{
}
