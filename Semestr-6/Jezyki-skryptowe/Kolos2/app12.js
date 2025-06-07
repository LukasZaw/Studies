const express = require("express");
const { MongoClient } = require("mongodb");
const fs = require("fs");
const path = require("path");

const app = express();
const PORT = 3000;
const MONGO_URL =
  "mongodb+srv://lukaszzawodz:ZAQ!2wsx@clusterstudia.4xnp0.mongodb.net/?retryWrites=true&w=majority&appName=ClusterStudia";
const DB_NAME = "Prod";

app.use(express.urlencoded({ extended: true }));

app.get("/", async (req, res) => {
  let client;
  try {
    client = await MongoClient.connect(MONGO_URL);
    const db = client.db(DB_NAME);
    const produkty = await db.collection("produkty").find().toArray();

    let html = `
            <html>
            <head>
                <title>Lista produktów</title>
                <meta charset="UTF-8">
            </head>
            <body>
                <h1>Lista produktów</h1>
                <a href="/dodaj">Dodaj produkt</a>
                <table border="1" cellpadding="5" cellspacing="0">
                    <tr>
                        <th>Nazwa</th>
                        <th>Opis</th>
                        <th>Cena</th>
                        <th>Ilość</th>
                        <th>Kategoria</th>
                    </tr>
                    ${produkty
                      .map(
                        (p) => `
                        <tr>
                            <td>${p.nazwa || ""}</td>
                            <td>${p.opis || ""}</td>
                            <td>${p.cena || ""}</td>
                            <td>${p.ilosc || ""}</td>
                            <td>${p.kategoria || ""}</td>
                        </tr>
                    `
                      )
                      .join("")}
                </table>
            </body>
            </html>
        `;
    res.send(html);
  } catch (err) {
    res.status(500).send("Błąd połączenia z bazą danych");
  } finally {
    if (client) await client.close();
  }
});

app.get("/dodaj", (req, res) => {
  res.send(`
    <html>
    <head>
      <title>Dodaj produkt</title>
      <meta charset="UTF-8">
    </head>
    <body>
      <h1>Dodaj nowy produkt</h1>
      <form method="POST" action="/dodaj">
        <label>Nazwa: <input type="text" name="nazwa" required></label><br>
        <label>Opis: <input type="text" name="opis" required></label><br>
        <label>Cena: <input type="number" step="0.01" name="cena" required></label><br>
        <label>Ilość: <input type="number" name="ilosc" required></label><br>
        <label>Kategoria: <input type="text" name="kategoria" required></label><br>
        <button type="submit">Dodaj</button>
      </form>
      <a href="/">Powrót do listy</a>
    </body>
    </html>
  `);
});

app.post("/dodaj", async (req, res) => {
  let client;
  try {
    client = await MongoClient.connect(MONGO_URL);
    const db = client.db(DB_NAME);
    const produkt = {
      nazwa: req.body.nazwa,
      opis: req.body.opis,
      cena: parseFloat(req.body.cena),
      ilosc: parseInt(req.body.ilosc),
      kategoria: req.body.kategoria,
    };
    await db.collection("produkty").insertOne(produkt);
    res.redirect("/");
  } catch (err) {
    res.status(500).send("Błąd zapisu do bazy danych");
  } finally {
    if (client) await client.close();
  }
});

app.listen(PORT, () => {
  console.log(`Serwer działa na http://localhost:${PORT}`);
});
