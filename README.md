# my-pokedex

## Greetings
Welcome fellow traveler. It's time to dive into the world of hooks. You might even "hook" some Pokemon 😅

### The objective
Implement a Pokedex using react hooks.

### Scoring
- (10 pt) Display a list of the Pokemon
- (10 pt) Select a Pokemon and open in a modal with more information
- (10 pt) Use refs to implement an close on click outside the modal
- (10 pt) Search a Pokemon by name
- (10 pt) Navigate inside a modal to the next/previous Pokemon using the arrow keys
- (10 pt) Mark a Pokemon as favorite

### Resources
- Basic UI to copy: https://pokedex.org/
- GraphQL API https://graphql-pokemon.now.sh/

### Scoring and Reward
The team with the highest score wins. E.g. if team A has 50 points and team B has 40 points, team A will be the winner. (Please don't name your team either A or B, they are taken!) The reward will depend on the winners.

## Run Project

```sh
npm install
npm start
# in another tab
npm run webpack
```

After you see the webpack compilation succeed (the `npm run webpack` step), open up `build/index.html` (**no server needed!**). Then modify whichever `.re` file in `src` and refresh the page to see the changes.

**For more elaborate ReasonReact examples**, please see https://github.com/reasonml-community/reason-react-example

## Run Project with Server

To run with the webpack development server run `npm run server` and view in the browser at http://localhost:8000. Running in this environment provides hot reloading and support for routing; just edit and save the file and the browser will automatically refresh.

Note that any hot reload on a route will fall back to the root (`/`), so `ReasonReact.Router.dangerouslyGetInitialUrl` will likely be needed alongside the `ReasonReact.Router.watchUrl` logic to handle routing correctly on hot reload refreshes or simply opening the app at a URL that is not the root.

To use a port other than 8000 set the `PORT` environment variable (`PORT=8080 npm run server`).

