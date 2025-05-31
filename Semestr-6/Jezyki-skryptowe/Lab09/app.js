const express = require("express");
const app = express();
const path = require("path");
const { MongoClient, ObjectId } = require("mongodb");

const uri =
  "mongodb+srv://lukaszzawodz:ZAQ!2wsx@clusterstudia.4xnp0.mongodb.net/?retryWrites=true&w=majority&appName=ClusterStudia";
const dbName = "carDatabase";
const collectionName = "cars";

app.use(express.static(__dirname));
app.use(express.json());

app.get("/cars", async (req, res) => {
  const client = new MongoClient(uri, {
    tlsAllowInvalidCertificates: true,
    tlsCAFile: undefined,
  });

  try {
    await client.connect();
    const db = client.db(dbName);
    const collection = db.collection(collectionName);
    const cars = await collection.find().toArray();
    res.json(cars);
  } catch (err) {
    res.status(500).json({ error: "Błąd połączenia z bazą danych" });
  } finally {
    await client.close();
  }
});

app.post("/cars", async (req, res) => {
  let { model, marka, moc, kolor, rok_produkcji } = req.body;
  if (!model || !marka || !moc || !kolor || !rok_produkcji) {
    return res.status(400).json({ error: "Brak wymaganych pól" });
  }

  moc = Number(moc);
  rok_produkcji = Number(rok_produkcji);

  const client = new MongoClient(uri, {
    tlsAllowInvalidCertificates: true,
    tlsCAFile: undefined,
  });

  try {
    await client.connect();
    const db = client.db(dbName);
    const collection = db.collection(collectionName);
    const result = await collection.insertOne({
      model,
      marka,
      moc,
      kolor,
      rok_produkcji,
    });
    res.status(201).json({ insertedId: result.insertedId });
  } catch (err) {
    res.status(500).json({ error: "Błąd dodawania samochodu" });
  } finally {
    await client.close();
  }
});

app.get("/brands", async (req, res) => {
  const client = new MongoClient(uri, {
    tlsAllowInvalidCertificates: true,
    tlsCAFile: undefined,
  });

  try {
    await client.connect();
    const db = client.db(dbName);
    const collection = db.collection(collectionName);
    const brands = await collection.distinct("marka");
    res.json(brands);
  } catch (err) {
    res.status(500).json({ error: "Błąd pobierania marek" });
  } finally {
    await client.close();
  }
});

app.get("/cars/brand/:brand", async (req, res) => {
  const brand = req.params.brand;
  const client = new MongoClient(uri, {
    tlsAllowInvalidCertificates: true,
    tlsCAFile: undefined,
  });

  try {
    await client.connect();
    const db = client.db(dbName);
    const collection = db.collection(collectionName);
    const cars = await collection.find({ marka: brand }).toArray();
    res.json(cars);
  } catch (err) {
    res.status(500).json({ error: "Błąd pobierania aut danej marki" });
  } finally {
    await client.close();
  }
});

app.delete("/cars/:id", async (req, res) => {
  const id = req.params.id;
  const client = new MongoClient(uri, {
    tlsAllowInvalidCertificates: true,
    tlsCAFile: undefined,
  });

  try {
    await client.connect();
    const db = client.db(dbName);
    const collection = db.collection(collectionName);
    const result = await collection.deleteOne({ _id: new ObjectId(id) });
    if (result.deletedCount === 1) {
      res.json({ success: true });
    } else {
      res.status(404).json({ error: "Nie znaleziono auta" });
    }
  } catch (err) {
    res.status(500).json({ error: "Błąd usuwania auta" });
  } finally {
    await client.close();
  }
});

app.delete("/brands/:brand", async (req, res) => {
  const brand = req.params.brand;
  const client = new MongoClient(uri, {
    tlsAllowInvalidCertificates: true,
    tlsCAFile: undefined,
  });

  try {
    await client.connect();
    const db = client.db(dbName);
    const collection = db.collection(collectionName);
    const result = await collection.deleteMany({ marka: brand });
    res.json({ deletedCount: result.deletedCount });
  } catch (err) {
    res.status(500).json({ error: "Błąd usuwania marki" });
  } finally {
    await client.close();
  }
});

// Start serwera
const PORT = 3000;
app.listen(PORT, () => {
  console.log(`Serwer działa na http://localhost:${PORT}`);
});
