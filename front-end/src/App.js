
import './App.css';
import GraphGenerator from './components/graphGenerator';

function App() {
  return (
    <div className="App">
      <header className="App-header">
        <h1>🦈AO3-TRAWLER🦈</h1>
      </header>
      <div className="box">
        <p>Welcome to AO3 TRAWLER!</p>
        <p>Choose your 2 Fanction works from the lists below.</p>
        <p></p> 
        <GraphGenerator/>
      </div>
    </div>
  );
}

export default App;
