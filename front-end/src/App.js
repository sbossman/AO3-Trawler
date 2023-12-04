
import './App.css';
import GraphGenerator from './components/graphGenerator';

function App() {
  return (
    <div className="App">
      <header className="App-header">
        <h1>🦈AO3-TRAWLER🦈</h1>
      </header>
      <div className="box">
        <h2>Welcome to AO3 TRAWLER!</h2>
        <p>Choose 2 Fanction works from the lists below.</p>
        <p> and check out the existing connections between them!</p> 
        <GraphGenerator/>
      </div>
    </div>
  );
}

export default App;
