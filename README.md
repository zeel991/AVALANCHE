
# CPay – Prefilled QR Payment Infrastructure

**CPay** is a complete payment infrastructure that allows merchants to generate **prefilled QR codes** for crypto payments and enables businesses to easily integrate these prefilled QR payments into their websites. It combines **hardware and software solutions** to create a seamless, secure, and user-friendly payment experience.

---

## Features

### Merchant Side
- Merchants can generate **prefilled QR codes** for accepting crypto payments.
- Money box hardware displays the QR code using **signal bus input**.
- The hardware wallet inside the money box securely stores the merchant’s **private key** and **token** for dashboard access.
- Merchants can track payments and manage transactions via a **dashboard**.

### User Side
- Users can scan the prefilled QR code to make payments quickly and securely.
- Integration with the **npm package** allows businesses to display QR payments directly on their website.

### NPM Package for Businesses
- Easy integration of prefilled QR payments into websites or web apps.
- Provides **user-side and merchant-side components**.
- Enables developers to create **customized payment experiences** with minimal setup.

---

## Hardware Integration
- **Money Box**: A secure device that displays the QR code and handles crypto payments.
- Contains a **hardware wallet** for private key management.
- Communicates with the dashboard via **secure signals**.

---

## Installation

### For Businesses (NPM Package)
```bash
npm install cpay-kit
````

### For Merchant Dashboard

Clone the repository and follow setup instructions to run the dashboard:

```bash
git clone https://github.com/zeel991/cpay.git
cd cpay
npm install
npm run start
```

---

## Usage

### Merchant Side

1. Generate a new prefilled QR payment:

```javascript
import { createPaymentPayload, generateQr } from "cpay-kit";

const payload = createPaymentPayload({
  merchantAddress: "0xMerchantAddress",
  amount: "100",
  token: "USDC",
  chainId: 1
});

const qr = await generateQr(payload);
// Display the QR in the money box or web dashboard
```

### User Side

1. Scan the QR code using any compatible wallet.
2. Payment is automatically populated with the correct merchant, amount, and token.
3. Transaction is confirmed on-chain.

---

## Dashboard Access

* Merchants can log in using the **hardware wallet token**.
* Track payments, view history, and manage QR codes securely.

---

## Demo links

```
dashboard - https://dashboard-phi-two-55.vercel.app
user side - https://user-app-zeta-neon.vercel.app
merchant side  - https://merchant-app-ruby.vercel.app/
npm package - https://www.npmjs.com/package/cpay-kit
```

---

## Security

* Private keys are securely stored in the **money box hardware wallet**.
* Dashboard access is token-protected.
* All payments are **prefilled and verified on-chain** to prevent errors or fraud.

---

## Future Enhancements

* Support for multiple tokens and chains.
* Advanced analytics on merchant dashboard.
* Mobile-friendly user interface for easier QR scanning.
* Automated reward system or cashback for users.

---

## Contributing

Contributions are welcome! Please fork the repository, make your changes, and create a pull request.

---

## License

MIT License



