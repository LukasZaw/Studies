import { useState } from "react";
import { useNavigate, useParams } from "react-router-dom";
import type { Contact } from "../Model/Contact";
import type { Category } from "../Model/Category";
import { Email } from "../Model/Email";

type RouteParams = {
  id: string;
};

type Props = {
  contacts: Contact[];
  onContactUpdated: (contact: Contact) => void;
};

const EditContact = ({ contacts, onContactUpdated }: Props) => {
  const { id } = useParams<RouteParams>();
  const navigate = useNavigate();
  const contactId = Number(id);
  const contact = contacts.find((c) => c.id === contactId);

  const [firstName, setFirstName] = useState(contact?.firstName ?? "");
  const [lastName, setLastName] = useState(contact?.lastName ?? "");
  const [age, setAge] = useState(contact ? String(contact.age) : "");
  const [sex, setSex] = useState(contact ? String(contact.sex) : "0");
  const [emailValue, setEmailValue] = useState(
    contact && contact.emails[0] ? contact.emails[0].value : "",
  );
  const [emailCategory, setEmailCategory] = useState(
    contact && contact.emails[0] ? contact.emails[0].category.name : "Prywatne",
  );

  if (!contact) {
    return <p>Kontakt nie został znaleziony.</p>;
  }

  const handleSubmit = (e: React.FormEvent<HTMLFormElement>) => {
    e.preventDefault();
    if (!firstName || !lastName || !age || !emailValue) {
      return;
    }

    const category: Category = {
      id: emailCategory === "Prywatne" ? 1 : 2,
      name: emailCategory,
    };

    const updatedContact: Contact = {
      ...contact,
      firstName,
      lastName,
      age: Number(age),
      sex: Number(sex),
      emails: [new Email(emailValue, category)],
    };

    onContactUpdated(updatedContact);
    navigate(`/person/${contact.id}`);
  };

  return (
    <div>
      <h2>Edytuj kontakt</h2>
      <form onSubmit={handleSubmit}>
        <div>
          <label>
            Imię:
            <input
              value={firstName}
              onChange={(e) => setFirstName(e.target.value)}
            />
          </label>
        </div>
        <div>
          <label>
            Nazwisko:
            <input
              value={lastName}
              onChange={(e) => setLastName(e.target.value)}
            />
          </label>
        </div>
        <div>
          <label>
            Wiek:
            <input
              type="number"
              value={age}
              onChange={(e) => setAge(e.target.value)}
            />
          </label>
        </div>
        <div>
          <label>
            Płeć:
            <select value={sex} onChange={(e) => setSex(e.target.value)}>
              <option value="0">Mężczyzna</option>
              <option value="1">Kobieta</option>
            </select>
          </label>
        </div>
        <div>
          <label>
            E-mail (pierwszy):
            <input
              type="email"
              value={emailValue}
              onChange={(e) => setEmailValue(e.target.value)}
            />
          </label>
        </div>
        <div>
          <label>
            Typ e-maila:
            <select
              value={emailCategory}
              onChange={(e) => setEmailCategory(e.target.value)}
            >
              <option value="Prywatne">Prywatne</option>
              <option value="Służbowe">Służbowe</option>
            </select>
          </label>
        </div>
        <button type="submit">Zapisz zmiany</button>
      </form>
    </div>
  );
};

export default EditContact;
