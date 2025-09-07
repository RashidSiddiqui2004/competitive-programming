#include <iostream>
using namespace std;

const string reconciliation(const vector<string> &invoices, const string &paymentString)
{
    // payment: "payment5,1000,Paying off: invoiceC"
    // payment: {PAYMENTID, AMOUNT, "Paying off: INVOICEID"}
    int commaPosition = std::find(paymentString.begin(), paymentString.end(), ',') - paymentString.begin();
    string paymentid = paymentString.substr(0, commaPosition);
    string remainingPaymentString = paymentString.substr(commaPosition + 1);
    commaPosition = find(remainingPaymentString.begin(), remainingPaymentString.end(), ',') - remainingPaymentString.begin();
    string amount = remainingPaymentString.substr(0, commaPosition);

    int invoiceidStartIndex = find(remainingPaymentString.begin(), remainingPaymentString.end(), ':') - remainingPaymentString.begin();
    string invoiceId = remainingPaymentString.substr(invoiceidStartIndex + 2);

    string dueDate = "";

    for (auto &invoice : invoices)
    {
        int index = find(invoice.begin(), invoice.end(), ',') - invoice.begin();
        string currentInvoiceId = invoice.substr(0, index);
        if (currentInvoiceId == invoiceId)
        {
            string remString = invoice.substr(index + 1);
            int dateendindex = find(remString.begin(), remString.end(), ',') - remString.begin();
            string currentAmount = remString.substr(dateendindex + 1);
            if (currentAmount == amount)
            {
                dueDate = remString.substr(0, dateendindex);
            }
            break;
        }
    }

    if (dueDate == "")
    {
        throw runtime_error("Corresponding invoice not found in database");
    }

    // payment5 pays off 1000 for invoiceC due on 2023-01-30
    const string summary = paymentid + " pays off " + amount + " for " + invoiceId + " due on " + dueDate;
    return summary;
}

int main()
{
    string paymentString = "";
    getline(cin, paymentString);

    int numberOfInvoices;
    cin >> numberOfInvoices;

    vector<string> invoices(numberOfInvoices);
    for (size_t i = 0; i < numberOfInvoices; i++)
    {
        cin >> invoices[i];
    }

    cout << reconciliation(invoices, paymentString);
    return 0;
}