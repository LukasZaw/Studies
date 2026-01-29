// ng new Angular --minimal=true --no-standalone
// ng generate component komp
// ng serve

import { Component } from "@angular/core";

@Component({
  selector: "app-root",
  template: ` <h1>Welcome to {{ title }}!</h1> `,
  standalone: false,
  styles: [],
})
export class AppComponent {
  title = "Angular";
}
