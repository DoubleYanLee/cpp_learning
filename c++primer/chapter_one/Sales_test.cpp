#include "Sales_item.h"

int main(){

	Sales_item total;

	if( std::cin >> total ){ //这个有点不一样 先读取一条记录
		Sales_item trans;

		while( std::cin >> trans ){ //然后读取剩下的记录

			if( total.isbn() == trans.isbn() )
				total += trans;
			else{
				std::cout << total << std::endl;
				total = trans;
			}
		}

		std::cout << total << std::endl;
	}else{

		std::cerr << "No data!" << std::endl;

		return -1;
	}

}





















