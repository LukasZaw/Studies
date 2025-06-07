// Import wymaganych modułów
const express = require("express");
const { MongoClient, ObjectId } = require("mongodb");
const fs = require("fs");
const path = require("path");

// Inicjalizacja aplikacji Express
const app = express();
const PORT = 3000;
// Adres URL do bazy MongoDB
const MONGO_URL =
  "mongodb+srv://lukaszzawodz:ZAQ!2wsx@clusterstudia.4xnp0.mongodb.net/?retryWrites=true&w=majority&appName=ClusterStudia";
// Nazwa bazy danych
const DB_NAME = "Prod";

// Middleware do obsługi danych z formularzy (POST)
app.use(express.urlencoded({ extended: true }));

// Strona główna - lista produktów z filtrowaniem po kategorii
app.get("/", async (req, res) => {
  let client;
  try {
    // Połączenie z bazą danych
    client = await MongoClient.connect(MONGO_URL);
    const db = client.db(DB_NAME);

    // Pobierz unikalne kategorie z kolekcji
    const kategorie = await db.collection("produkty").distinct("kategoria");

    // Pobierz wybraną kategorię z query string (?kategoria=...)
    const wybranaKategoria = req.query.kategoria;

    // Przygotuj filtr do zapytania
    const filter =
      wybranaKategoria && wybranaKategoria !== "Wszystkie"
        ? { kategoria: wybranaKategoria }
        : {};

    // Pobierz produkty z bazy, ewentualnie przefiltrowane po kategorii
    const produkty = await db.collection("produkty").find(filter).toArray();

    // Wygeneruj linki do filtrowania po kategoriach
    const kategoriaLinks = [
      `<a href="/"${
        !wybranaKategoria || wybranaKategoria === "Wszystkie"
          ? ' style="font-weight:bold"'
          : ""
      }>Wszystkie</a>`,
    ]
      .concat(
        kategorie.map(
          (kat) =>
            `<a href="/?kategoria=${encodeURIComponent(kat)}"${
              wybranaKategoria === kat ? ' style="font-weight:bold"' : ""
            }>${kat}</a>`
        )
      )
      .join(" | ");

    // Wygeneruj HTML strony głównej z tabelą produktów
    let html = `
            <html>
            <head>
                <title>Lista produktów</title>
                <meta charset="UTF-8">
            </head>
            <body>
                <h1>Lista produktów</h1>
                <a href="/dodaj">Dodaj produkt</a>
                <div style="margin:10px 0;">${kategoriaLinks}</div>
                <table border="1" cellpadding="5" cellspacing="0">
                    <tr>
                        <th>Nazwa</th>
                        <th>Opis</th>
                        <th>Cena</th>
                        <th>Ilość</th>
                        <th>Kategoria</th>
                        <th>Akcje</th>
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
                            <td>
                              <a href="/edytuj/${p._id}">Edytuj</a>
                              <form method="POST" action="/usun/${
                                p._id
                              }" style="display:inline;">
                                <button type="submit" onclick="return confirm('Na pewno usunąć?')">Usuń</button>
                              </form>
                            </td>
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
    // Obsługa błędów połączenia z bazą
    res.status(500).send("Błąd połączenia z bazą danych");
  } finally {
    // Zamknięcie połączenia z bazą
    if (client) await client.close();
  }
});

// Formularz dodawania nowego produktu (GET)
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

// Obsługa dodawania nowego produktu (POST)
app.post("/dodaj", async (req, res) => {
  let client;
  try {
    // Połączenie z bazą i dodanie produktu
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
    // Obsługa błędów zapisu
    res.status(500).send("Błąd zapisu do bazy danych");
  } finally {
    if (client) await client.close();
  }
});

// Formularz edycji produktu (GET)
app.get("/edytuj/:id", async (req, res) => {
  let client;
  try {
    // Połączenie z bazą i pobranie produktu po ID
    client = await MongoClient.connect(MONGO_URL);
    const db = client.db(DB_NAME);
    const produkt = await db
      .collection("produkty")
      .findOne({ _id: new ObjectId(req.params.id) });
    if (!produkt) {
      res.status(404).send("Nie znaleziono produktu");
      return;
    }
    // Formularz edycji z wypełnionymi danymi produktu
    res.send(`
      <html>
      <head>
        <title>Edytuj produkt</title>
        <meta charset="UTF-8">
      </head>
      <body>
        <h1>Edytuj produkt</h1>
        <form method="POST" action="/edytuj/${produkt._id}">
          <label>Nazwa: <input type="text" name="nazwa" value="${
            produkt.nazwa || ""
          }" required></label><br>
          <label>Opis: <input type="text" name="opis" value="${
            produkt.opis || ""
          }" required></label><br>
          <label>Cena: <input type="number" step="0.01" name="cena" value="${
            produkt.cena || ""
          }" required></label><br>
          <label>Ilość: <input type="number" name="ilosc" value="${
            produkt.ilosc || ""
          }" required></label><br>
          <label>Kategoria: <input type="text" name="kategoria" value="${
            produkt.kategoria || ""
          }" required></label><br>
          <button type="submit">Zapisz zmiany</button>
        </form>
        <a href="/">Powrót do listy</a>
      </body>
      </html>
    `);
  } catch (err) {
    // Obsługa błędów pobierania produktu
    res.status(500).send("Błąd pobierania produktu");
  } finally {
    if (client) await client.close();
  }
});

// Obsługa zapisu edycji produktu (POST)
app.post("/edytuj/:id", async (req, res) => {
  let client;
  try {
    // Połączenie z bazą i aktualizacja produktu po ID
    client = await MongoClient.connect(MONGO_URL);
    const db = client.db(DB_NAME);
    await db.collection("produkty").updateOne(
      { _id: new ObjectId(req.params.id) },
      {
        $set: {
          nazwa: req.body.nazwa,
          opis: req.body.opis,
          cena: parseFloat(req.body.cena),
          ilosc: parseInt(req.body.ilosc),
          kategoria: req.body.kategoria,
        },
      }
    );
    res.redirect("/");
  } catch (err) {
    // Obsługa błędów aktualizacji
    res.status(500).send("Błąd aktualizacji produktu");
  } finally {
    if (client) await client.close();
  }
});

// Obsługa usuwania produktu (POST)
app.post("/usun/:id", async (req, res) => {
  let client;
  try {
    // Połączenie z bazą i usunięcie produktu po ID
    client = await MongoClient.connect(MONGO_URL);
    const db = client.db(DB_NAME);
    await db
      .collection("produkty")
      .deleteOne({ _id: new ObjectId(req.params.id) });
    res.redirect("/");
  } catch (err) {
    // Obsługa błędów usuwania
    res.status(500).send("Błąd usuwania produktu");
  } finally {
    if (client) await client.close();
  }
});

// Uruchomienie serwera na porcie 3000
app.listen(PORT, () => {
  console.log(`Serwer działa na http://localhost:${PORT}`);
});
