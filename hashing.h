#ifndef HASHING_H_INCLUDED
#define HASHING_H_INCLUDED
int sint2int(string num )
{
    int k = 1;
    int n= num.size();
    // For handling negative numbers
    if (num.substr(0,1) == "-")
    {
        k=-1;
        n--;
        num = num.substr(1);
    }
    int ans=0;
    for (int r=0 ; r<n ; r++)
    {
        ans = ans*10 + ((int)num[r] - 48);
    }
    return ans*k;
}
string int2sint(int num)
{
	string ans;
	string sign = "";
	if(num < 0){sign = "-";}
	while( num>0)
	{
		int a = num%10;
		ans = (char)(a+48) + ans;
		num /= 10;
	}
	if (ans.size() == 0){ans = "0";}
	ans = sign + ans;
	return ans;
}
int timestamp2int(string timestamp)
{
    string year = "", month = "", day = "";
    int mode = 0;
    for(int i = 0; i < timestamp.size(); i++)
    {
        if(timestamp[i] == '/')
        {
            mode++;
            continue;
        }
        if(mode == 0)
        {
            year += timestamp[i];
        }
        else if(mode == 1)
        {
            month += timestamp[i];
        }
        else if(mode == 2)
        {
            day += timestamp[i];
        }
    }

    int y = sint2int(year), m = sint2int(month), d = sint2int(day);
    if(m > 12)
    {
        throw("Month must be less than or equal to 12!\n");
    }
    if(d > 31)
    {
        throw("We do not have " + day + " days in a month!\n");
    }
    return 372 * y + 31 * (m - 1) + d - 1;

}
string int2timestamp(int date)
{
    int year = date / 372;
    date = date % 372;
    int month = date / 31 + 1, day = date % 31 + 1;
    return int2sint(year) + "/" + int2sint(month) + "/" + int2sint(day);


}
#endif // HASHING_H_INCLUDED
