#include "string"


class INotifier{
public:
    virtual void Notify(const string& message) const = 0;
};
class SmsNotifier : public INotifier{
public:
    SmsNotifier(const string& s) : number_(s){};
    void Notify(const string &message) const override{
        SendSms(number_, message);
    }
private:
    string number_;
};
class EmailNotifier : public INotifier{
public:
    EmailNotifier(const string& s) : email_(s){};
    void Notify(const string &message) const override{
        SendEmail(email_, message);
    }
private:
    string email_;
};

void Notify(INotifier& notifier, const string& message) {
    notifier.Notify(message);
}