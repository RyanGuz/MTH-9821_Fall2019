
// stl
#include <iostream>
#include <memory>

// user defined
#include "European_Option.h"
#include "Binomial_Tree_Pricer.h"
#include "Black_Scholes.h"

int main()
{
	std::shared_ptr<European_Option> euro_put
		= std::make_shared<European_Put>(50, 54, .025, .01, .28, 1);

	Binomial_Tree_Pricer btp(euro_put);

	std::cout << "bs price: " << euro_put->bs_price() << "\n";
	std::cout << "bs delta: " << euro_put->bs_delta() << "\n";

	btp.change_timesteps(200);
	btp.print();
}