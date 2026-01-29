import "./App.css";
import { useState } from "react";
import { Routes, Route, Link } from "react-router-dom";
import PearsonList from "./Components/PearsonList";
import PearsonDetails from "./Components/PearsonDetails";
import ExpandableContactList from "./Components/ExpandableContactList";
import CreateContact from "./Components/CreateContact";
import EditContact from "./Components/EditContact";
import { sampleContacts, Contact } from "./Model/Contact";

function App() {
  const [contacts, setContacts] = useState<Contact[]>(sampleContacts);

  const handleContactCreated = (contact: Contact) => {
    setContacts((prev) => [...prev, contact]);
  };

  const handleContactUpdated = (updated: Contact) => {
    setContacts((prev) => prev.map((c) => (c.id === updated.id ? updated : c)));
  };

  const nextId =
    contacts.length > 0 ? Math.max(...contacts.map((c) => c.id)) + 1 : 1;

  return (
    <div className="App">
      <h1>Lista osób - React Router</h1>
      <nav style={{ marginBottom: "1rem" }}>
        <Link to="/">Lista z przejściem na szczegóły</Link> |{" "}
        <Link to="/contacts-inline">Lista rozwijana</Link> |{" "}
        <Link to="/create">Dodaj kontakt</Link>
      </nav>
      <Routes>
        <Route path="/" element={<PearsonList contacts={contacts} />} />
        <Route
          path="/person/:id"
          element={<PearsonDetails contacts={contacts} />}
        />
        <Route
          path="/contacts-inline"
          element={<ExpandableContactList contacts={contacts} />}
        />
        <Route
          path="/create"
          element={
            <CreateContact
              nextId={nextId}
              onContactCreated={handleContactCreated}
            />
          }
        />
        <Route
          path="/edit/:id"
          element={
            <EditContact
              contacts={contacts}
              onContactUpdated={handleContactUpdated}
            />
          }
        />
      </Routes>
    </div>
  );
}

export default App;
