import { useState } from "react";
import type { Contact } from "../Model/Contact";

type Props = {
  contacts: Contact[];
};

const ExpandableContactList = ({ contacts }: Props) => {
  const [expandedId, setExpandedId] = useState<number | null>(null);

  const toggle = (id: number) => {
    setExpandedId((current) => (current === id ? null : id));
  };

  return (
    <div>
      <h2>Lista kontaktów</h2>
      <ul>
        {contacts.map((contact) => {
          const isExpanded = expandedId === contact.id;
          return (
            <li key={contact.id}>
              <p>
                {contact.firstName} {contact.lastName}
              </p>
              <button onClick={() => toggle(contact.id)}>
                {isExpanded ? "Ukryj" : "Rozwiń"}
              </button>

              {isExpanded && (
                <div>
                  <p>
                    <strong>Wiek:</strong> {contact.age}
                  </p>
                  <p>
                    <strong>Płeć:</strong>{" "}
                    {contact.sex === 0 ? "Mężczyzna" : "Kobieta"}
                  </p>
                  <p>
                    <strong>Adresy e-mail:</strong>
                  </p>
                  <ul>
                    {contact.emails.map((email, index) => (
                      <li key={index}>
                        {email.value} ({email.category.name})
                      </li>
                    ))}
                  </ul>
                </div>
              )}
            </li>
          );
        })}
      </ul>
    </div>
  );
};

export default ExpandableContactList;
