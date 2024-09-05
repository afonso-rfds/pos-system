
# POS Supermarket System

This project is a C++ point-of-sale (POS) system for managing product registration, invoicing, and payments in a supermarket. It uses a state machine and singleton pattern to handle transactions efficiently.

## Tool Requirements
- Requirements
- C++11
- CMake
- GoogleTest
- SQLite

## Features

- **Main Menu**: Start a new transaction, show saved invoices, delete saved invoices, or exit the program.
- **Operator Identification**: Start by selecting an operator name to identify yourself.
- **Product Registration**: Enter EAN13 codes to fetch product details from the products database:
  - `0000000000000` - Apple - €0.50
  - `0000000000001` - Candy Bar - €1.00
  - `0000000000002` - Water - €0.75
  - `0000000000003` - Eggs - €3.55
  - `0000000000004` - Bread - €1.25
- **Partial Payments**: Support for multiple payment methods (MBWay, card, cash). If paying with cash, overpayments are accepted, and change is calculated and displayed.
- **Transaction History**: Save each completed transaction in the invoice database.

## States
The system operates through the following states:
- **Idle**: The system is waiting for an action.
- **Ready**: The operator has been identified, and the system is ready to start a new transaction.
- **Items**: Products are being registered.
- **PaymentSelection**: Choose a payment method.
- **PartialPayment**: Accept partial payments.
- **PaymentCompletion**: Finalize the transaction, calculate change if necessary, and generate the receipt.

## Design Patterns
- **Singleton**: Used for managing product and invoice databases.
- **State**: Implements the POS state machine to manage transitions between different transaction phases.

## Compilation

1. Clone the repository:
   ```bash
   git clone https://github.com/afonso-rfds/pos-exercise.git
   cd pos-exercise
   ```

2. Build the project using CMake:
   ```bash
   mkdir build
   cd build
   cmake ..
   make
   ```

## Running the Program

After building, you can run the program with:
```bash
./pos_supermarket
```

Start by selecting an operator, register products, process payments, and save or view previous transactions.