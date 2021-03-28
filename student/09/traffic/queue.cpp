#include "queue.hh"
#include <iostream>

// Implement the member functions of Queue here

Queue::Queue(unsigned int cycle):first_(nullptr),last_(nullptr)
{
    cycle_ = cycle;
    max_cycle_ = cycle;
}

Queue::~Queue()
{
    first_ = nullptr;
    last_ = nullptr;

}

void Queue::enqueue(string reg)
{
    if (is_green_)
    {
        std::cout << "GREEN: The vehicle " << reg << " need not stop to wait" <<
                     std::endl;
        cycle_--;
        if (cycle_<=0)
        {
            is_green_ = false;
            cycle_ = max_cycle_;
        }
    }
    else
    {
        Vehicle* new_car = new Vehicle{reg,nullptr};

        if (first_ == nullptr)
        {
            first_ = new_car;
            last_ = new_car;
        }
        else
        {
            last_->next = new_car;
            last_ = new_car;
        }
    }
}

void Queue::switch_light()
{
    if (is_green_)
    {
        is_green_ = false;
        if (first_ == nullptr)
        {
            std::cout << "RED: No vehicles waiting in traffic lights"<<std::endl;
        }
        else
        {
            std::cout << "RED: Vehicle(s) ";
            Vehicle* current_car = first_;
            while (current_car != nullptr)
            {
                std::cout << current_car->reg_num <<" ";
                current_car = current_car->next;
            }
            std::cout << "waiting in traffic lights"<< std::endl;
        }
    }
    else
    {
        is_green_ = true;
        if (first_ == nullptr)
        {
            std::cout << "GREEN: No vehicles waiting in traffic lights"<<
                         std::endl;
        }
        else
        {
            std::cout<< "GREEN: Vehicle(s) ";
            Vehicle* current_car = first_;
            if (current_car != nullptr)
            {
                while (current_car != nullptr and cycle_>0)
                {
                    std::cout << current_car->reg_num <<" ";
                    current_car = current_car->next;
                    dequeue();
                }
                std::cout << "can go on"<<std::endl;

                is_green_ = false;
                cycle_ = max_cycle_;
            }
        }
    }
}

void Queue::reset_cycle(unsigned int cycle)
{
    max_cycle_ = cycle;
    cycle_ = cycle;
}

void Queue::print()
{
    string light = "";
    if (is_green_)
    {
        light = "GREEN:";
    }
    else
    {
        light = "RED:";
    }
    std::cout <<light;
    Vehicle* current_car = first_;

    if (current_car!=nullptr)
    {
        std::cout << " Vehicle(s) ";
        while(current_car!=nullptr)
        {
            std::cout<<current_car->reg_num<<" ";
            current_car=current_car->next;
        }
    }
    else
    {
        std::cout << " No vehicles ";
    }
    std::cout << "waiting in traffic lights"<< std::endl;

}


void Queue::dequeue()
{
    if (first_ == last_)
    {
        delete first_;
        first_ = nullptr;
        last_ = nullptr;
    }
    else if (first_->next == last_)
    {
        delete first_;
        first_ = last_;
    }
    else
    {
        Vehicle* new_first = first_->next;
        delete first_;
        first_ = new_first;
    }

    cycle_--;
}
