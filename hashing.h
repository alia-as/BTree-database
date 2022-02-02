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
        throw("I've never seen month no." + month + " in a year!!\n");
    }
    else if(m < 1)
    {
        throw("Maybe you forgot to write a month?!\n");
    }
    if(d > 31)
    {
        throw("A month has just 31 days, so day " + day + " is invalid!! :(\n");
    }
    else if(d < 1)
    {
        throw("Maybe you forgot to write a day?!\n");
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
long long string2int(string name)
{
    long long ans = 0, temp;
    name = name.substr(1, name.size() - 2);
    for(int i = 0; i < name.size(); i++)
    {
        temp = (int)name[i];
        if(temp >= 48 && temp <= 57)
        {
            temp -= 48;
        }
        else if(temp >= 97 && temp <= 122)
        {
            temp -= 87;
        }
        else
        {
            throw("String has unusual characters!!\n");
        }
        ans *= 36;
        ans += temp;
    }
    return ans;
}
string int2string(long long num)
{
    string name = "";
    char temp;
    while(num > 0)
    {
        if(num % 36 < 10)
        {
            temp = (num % 36 + 48);
        }
        else
        {
            temp = (num % 36 + 87);
        }
        name = temp + name;
        num /= 36;
    }
    return name;
}
#endif // HASHING_H_INCLUDED
