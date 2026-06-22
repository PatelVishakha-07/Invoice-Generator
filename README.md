# Invoice Generator

A console-based billing application built in C for general stores, designed to generate customer invoices and automatically update product stock after every sale.

## Overview

Small general stores often handle billing manually, which makes it easy to lose track of stock levels and sales records. This project automates that process — when a bill is generated for a customer's purchase, the corresponding product stock is updated automatically, keeping inventory data accurate without any extra manual effort.

## Features

- **Bill Generation** — enter products purchased by a customer and generate an itemized invoice
- **Automatic Stock Updates** — product stock is updated in real time as items are billed
- **Product Management** — maintain a record of available products and their quantities

## Tech Stack

- **Language:** C
- **Storage:** File-based 

## Getting Started

### Prerequisites
- A C compiler (GCC, Turbo C, or any standard C compiler)

### Setup & Run
1. Clone the repository
   ```bash
   git clone https://github.com/PatelVishakha-07/Invoice-Generator.git
   ```
2. Navigate to the project directory
   ```bash
   cd Invoice-Generator
   ```
3. Compile the program
   ```bash
   gcc main.c -o invoice_generator
   ```
4. Run the executable
   ```bash
   ./invoice_generator
   ```

## How It Works

1. The program displays available products and their stock
2. The user enters the products and quantities purchased by a customer
3. An invoice is generated showing item-wise cost and total amount
4. Stock for each purchased product is automatically reduced and updated

## Author

**Vishakha Patel**
[LinkedIn](https://www.linkedin.com/in/patelvishakha-tech)
