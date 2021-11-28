struct ValidateInfo
{
private:
    std::vector<int> container;
public:
    int max_acres_can_buy;
    int max_acres_can_sold;
    int max_wheat_can_eat;
    int max_acres_can_sow;
    int cost_per_acr;
    int max_acres_can_process;

    double operator[](int i)
    {
        container = {max_acres_can_buy, max_acres_can_sold, max_wheat_can_eat, max_acres_can_sow};
        return container[i];
    }
};