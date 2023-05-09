#include <cassert>
#include <iomanip>
#include <iostream>

#include "project4.hpp"
#include "History.hpp"
#include "Transaction.hpp"

////////////////////////////////////////////////////////////////////////////////
// Definitions for Transaction class
////////////////////////////////////////////////////////////////////////////////
//
//

// Constructor
// TASK 1
Transaction::Transaction (std::string ticker_symbol, unsigned int day_date, unsigned int month_date, unsigned year_date, bool buy_sell_trans, unsigned int number_shares, double trans_amount){
  symbol = ticker_symbol;
  day = day_date;
  month = month_date;
  year = year_date;
  if(buy_sell_trans == true){
    trans_type = "Buy";
  }else{
    trans_type = "Sell";
  }
  shares = number_shares; 
  amount = trans_amount;
  trans_id = assigned_trans_id;
  assigned_trans_id ++;
  p_next = nullptr;
  acb = 0.0;
  acb_per_share = 0.0;
  share_balance = 0;
  cgl = 0.0;
}



// Destructor
// TASK 1
Transaction::~Transaction(){
  if(this->p_next != nullptr){
    delete this->p_next;
    p_next = nullptr;
  }
}


// Overloaded < operator.
// TASK 2
bool Transaction::operator< (Transaction const & other){
  //'this' is the left operand (transaction 1) or we can just use the member variables directly
  //'other' is right operand (transaction 2)
  if(year < other.year){
    return true;
  }
  if((year == other.year) && (month < other.month)){
    return true;
  }
  if((year == other.year) && (month == other.month) && (day < other.day)){
    return true;
  }

  return false;
}


// GIVEN
// Member functions to get values.
//
std::string Transaction::get_symbol() const { return symbol; }
unsigned int Transaction::get_day() const { return day; }
unsigned int Transaction::get_month() const { return month; }
unsigned int Transaction::get_year() const { return year; }
unsigned int Transaction::get_shares() const { return shares; }
double Transaction::get_amount() const { return amount; }
double Transaction::get_acb() const { return acb; }
double Transaction::get_acb_per_share() const { return acb_per_share; }
unsigned int Transaction::get_share_balance() const { return share_balance; }
double Transaction::get_cgl() const { return cgl; }
bool Transaction::get_trans_type() const { return (trans_type == "Buy") ? true: false ; }
unsigned int Transaction::get_trans_id() const { return trans_id; }
Transaction *Transaction::get_next() { return p_next; }

// GIVEN
// Member functions to set values.
//
void Transaction::set_acb( double acb_value ) { acb = acb_value; }
void Transaction::set_acb_per_share( double acb_share_value ) { acb_per_share = acb_share_value; }
void Transaction::set_share_balance( unsigned int bal ) { share_balance = bal ; }
void Transaction::set_cgl( double value ) { cgl = value; }
void Transaction::set_next( Transaction *p_new_next ) { p_next = p_new_next; }

// GIVEN
// Print the transaction.
//
void Transaction::print() {
  std::cout << std::fixed << std::setprecision(2);
  std::cout << std::setw(4) << get_trans_id() << " "
    << std::setw(4) << get_symbol() << " "
    << std::setw(4) << get_day() << " "
    << std::setw(4) << get_month() << " "
    << std::setw(4) << get_year() << " ";


  if ( get_trans_type() ) {
    std::cout << "  Buy  ";
  } else { std::cout << "  Sell "; }

  std::cout << std::setw(4) << get_shares() << " "
    << std::setw(10) << get_amount() << " "
    << std::setw(10) << get_acb() << " " << std::setw(4) << get_share_balance() << " "
    << std::setw(10) << std::setprecision(3) << get_acb_per_share() << " "
    << std::setw(10) << std::setprecision(3) << get_cgl()
    << std::endl;
}


////////////////////////////////////////////////////////////////////////////////
// Definitions for the History class
////////////////////////////////////////////////////////////////////////////////
//
//


// Constructor
// TASK 3
History::History(){
  p_head = nullptr;
}


// Destructor
// TASK 3
History::~History(){
  delete this->p_head;
  p_head = nullptr;
}



// read_history(...): Read the transaction history from file.
// TASK 4
void History::read_history(){
  /*std::string ticker_symbol{};
  unsigned int day_date{};
  unsigned int month_date{};
  unsigned year_date{};
  bool buy_sell_trans{};
  unsigned int number_shares{};
  double trans_amount{};*/

  ece150::open_file();

  while(ece150::next_trans_entry() != false){
    //looping through each transaction in the txt file
    /*ticker_symbol = ece150::get_trans_symbol();
    day_date = ece150::get_trans_day();
    month_date = ece150::get_trans_month();
    year_date = ece150::get_trans_year();
    buy_sell_trans = ece150::get_trans_type();
    number_shares = ece150::get_trans_shares();
    trans_amount = ece150::get_trans_amount();*/

    //Transaction *p_transaction {new Transaction{ticker_symbol, day_date, month_date, year_date, buy_sell_trans, number_shares, trans_amount}};

    Transaction *p_transaction {new Transaction{ece150::get_trans_symbol(), ece150::get_trans_day(), ece150::get_trans_month(), ece150::get_trans_year(), ece150::get_trans_type(), ece150::get_trans_shares(), ece150::get_trans_amount()}};

    /*std::cout<< ticker_symbol;
    std::cout<< day_date ;
    std::cout<< month_date ;
    std::cout<< year_date;
    std::cout<< buy_sell_trans ;
    std::cout<< number_shares;
    std::cout<< trans_amount<<std::endl;*/

    /*std::cout<< ece150::get_trans_symbol();
    std::cout<< ece150::get_trans_day();
    std::cout<< ece150::get_trans_month();
    std::cout<< ece150::get_trans_year();
    std::cout<< ece150::get_trans_type();
    std::cout<< ece150::get_trans_shares();
    std::cout<< ece150::get_trans_amount();*/

 
    History::insert(p_transaction);    

  }

 

  ece150::close_file();
  
}

// insert(...): Insert transaction into linked list.
// TASK 5
void History::insert(Transaction *p_new_trans){

  Transaction *p_search{p_head};

  if(p_head == nullptr){
    p_head = p_new_trans;
    return;
  }

 while(p_search -> get_next() != nullptr){
    p_search = p_search -> get_next();
  }
    p_search -> set_next(p_new_trans);
    p_search = nullptr;
    return;
  
  //attended and followed along during Nov 17 Lab Session with Instructor Lau
}


// sort_by_date(): Sort the linked list by trade date.
// TASK 6
void History::sort_by_date(){
  Transaction *p_new_head {nullptr};
  Transaction *p_front {nullptr};
  

  while(p_head != nullptr){
    //isolating the front node in original list
    p_front = p_head;
    p_head = p_head -> get_next();
    p_front -> set_next(nullptr);

    //if the sorted list is empty
    if(p_new_head == nullptr){
      p_new_head = p_front;
      p_front = nullptr;
    }else{
      Transaction *p_search{p_new_head};


      //Inserting at the front of the list
      if(*p_front < *p_new_head){
        Transaction *p_temp{nullptr};
        p_temp = p_new_head;
        p_new_head = p_front;
        p_new_head -> set_next(p_temp);
        p_front = nullptr;
        p_temp = nullptr;

      //Getting to the spot that the transaction needs to be inserted
      }else{
        while((p_search -> get_next() != nullptr) && (*(p_search -> get_next()) < *p_front)){
          p_search = p_search -> get_next();
        }

        //insert it into the list
        p_front -> set_next(p_search->get_next());
        p_search -> set_next(p_front);
        p_front = nullptr;
        p_search = nullptr;
      }
    }


      
  //still need to check when dates are equal
  }

  //passing the sorted list to the original list
  p_head = p_new_head;
  p_new_head = nullptr;
  //end
}


// update_acb_cgl(): Updates the ACB and CGL values.
// TASK 7
void History::update_acb_cgl(){
  Transaction *p_search{p_head};
  double cgl{};
  double acb{};
  double acb_per_share{};
  double previous_acb_per_share{};
  unsigned int shares{};

  while(p_search != nullptr){
    if(p_search->get_trans_type() == true){
      acb += p_search->get_amount();
      shares += p_search->get_shares();
    }else{
      acb = acb - (p_search->get_shares() * acb_per_share);
      shares -= p_search->get_shares();
      cgl = p_search->get_amount() - (p_search->get_shares() * acb_per_share);
      p_search->set_cgl(cgl);
    }

    p_search -> set_acb(acb);
    p_search -> set_share_balance(shares);
    
    acb_per_share = (p_search -> get_acb())/(p_search-> get_share_balance());
    p_search -> set_acb_per_share(acb_per_share);

    previous_acb_per_share = acb_per_share;
    
    

    p_search = p_search -> get_next();
  }
  p_search = nullptr;
}



// compute_cgl(): )Compute the ACB, and CGL.
// TASK 8
double History::compute_cgl(unsigned int year){
  Transaction *p_search{p_head};
  double cgl{};

  while(p_search != nullptr){
    if(p_search->get_year() == year){
      cgl += p_search->get_cgl();
    }
    p_search = p_search -> get_next();

  }
  p_search = nullptr;
  return cgl;
}



// print() Print the transaction history.
//TASK 9
void History::print(){
  Transaction *p_traverse{p_head};
  
  std::cout<<"========== BEGIN TRANSACTION HISTORY ============" <<std::endl;
  while(p_traverse != nullptr){
    p_traverse->print();

    p_traverse = p_traverse -> get_next();




  }
  std::cout<<"========== END TRANSACTION HISTORY ============" <<std::endl;
  p_traverse = nullptr;
}



// GIVEN
// get_p_head(): Full access to the linked list.
//
Transaction *History::get_p_head() { return p_head; }
