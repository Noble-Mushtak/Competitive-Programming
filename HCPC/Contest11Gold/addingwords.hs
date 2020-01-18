import qualified Data.Map as M
import qualified Data.List as L
import Data.Maybe
import Debug.Trace

data State = State { getVars :: (M.Map String Integer), getInverseVars :: (M.Map Integer String), getOutput :: [String] -> [String] }

defaultState :: State
defaultState = State M.empty M.empty id

calcSign :: String -> Integer
calcSign "+" = 1
calcSign "-" = -1
calcSign _ = error "Oh noes"

calcSum :: Integer -> M.Map String Integer -> [String] -> Maybe Integer
calcSum sign vars [curVar, "="] =
  do
    curValue <- M.lookup curVar vars
    return $ sign*curValue
calcSum sign vars (curVar:curSign:tokens) =
  do
    curValue <- M.lookup curVar vars
    curSum <- calcSum (calcSign curSign) vars tokens
    return $ sign*curValue+curSum
calcSum _ vars _ = error "What?"

updateState :: State -> [String] -> State
updateState st [] = st
updateState st@(State vars invVars outputFunc) ("calc":tokens) =
  let output = do
                 curSum <- calcSum 1 vars tokens
                 M.lookup curSum invVars
      preOutput = (L.intercalate " " tokens)++" "
      trueOutput = preOutput++(fromMaybe "unknown" output) in
    State vars invVars $ outputFunc . (trueOutput : )
updateState (State vars invVars outputFunc) ["def", newVar, newValue] =
  let actualValue = read newValue in
    State (M.insert newVar actualValue vars)
          (M.insert actualValue newVar $ M.filter ((/=) newVar) invVars)
          outputFunc
updateState (State vars invVars outputFunc) ["clear"] =
  State M.empty M.empty outputFunc
updateState st tokens = error $ show tokens

outputState :: State -> String
outputState (State _ _ outputFunc) = L.intercalate "\n" $ outputFunc [""]

main :: IO ()
main = interact (outputState . L.foldl' updateState defaultState . map words . lines)