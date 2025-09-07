def getCompanyName(transactions):
    companyName = []
    for transaction in transactions:
        l = transaction.split(',')
        companyName.append(l.pop())
    return companyName

transactions = [
        "VISA,Jan,15.50,USD,Closed",
        "MasterCard,Feb,10.00,EUR,Open",
        "AMEX,Jan,12.75,GBP,Closed",
        "VISA,Mar,9.50,USD,Open",
        "Discover,Feb,8.25,INR,Closed",
        "MasterCard,Jan,20.00,USD,Open",
        "AMEX,Mar,5.00,EUR,Closed",
        "VISA,Feb,7.75,GBP,Closed",
        "Discover,Jan,11.00,USD,Open"
]

companyNames = getCompanyName(transactions=transactions)
print(companyNames)