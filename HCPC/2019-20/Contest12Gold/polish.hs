import qualified Data.List as L
import qualified Text.Read as R

data Expression = Number Integer | Variable String | Add Expression Expression | Subtract Expression Expression | Multiply Expression Expression deriving (Show)

parseOp :: String -> Maybe (Expression -> Expression -> Expression)
parseOp "+" = Just Add
parseOp "-" = Just Subtract
parseOp "*" = Just Multiply
parseOp _   = Nothing

parseExpression' :: [String] -> (Expression, [String])
parseExpression' (firstWord:words) =
  case (parseOp firstWord) of
    Just op ->
      let (expr1, restWords) = parseExpression' words
          (expr2, restRestWords) = parseExpression' restWords in
        (op expr1 expr2, restRestWords)
    Nothing ->
      case (R.readMaybe firstWord :: Maybe Integer) of
        Just constant -> (Number constant, words)
        Nothing       -> (Variable firstWord, words)

parseExpression :: [String] -> Expression
parseExpression words =
  case (parseExpression' words) of
    (answer, []) -> answer
    _            -> error $ "Could not parse expression: " ++ (show words)

simplifyExpression :: Expression -> Expression
simplifyExpression exp@(Number _) = exp
simplifyExpression exp@(Variable _) = exp
simplifyExpression exp@(Add exp1 exp2) =
  case ( (simplifyExpression exp1, simplifyExpression exp2) ) of
    (Number a, Number b) -> Number $ a+b
    (newExp1, newExp2)   -> Add newExp1 newExp2
simplifyExpression exp@(Subtract exp1 exp2) =
  case ( (simplifyExpression exp1, simplifyExpression exp2) ) of
    (Number a, Number b) -> Number $ a-b
    (newExp1, newExp2)   -> Subtract newExp1 newExp2
simplifyExpression exp@(Multiply exp1 exp2) =
  case ( (simplifyExpression exp1, simplifyExpression exp2) ) of
    (Number a, Number b) -> Number $ a*b
    (newExp1, newExp2)   -> Multiply newExp1 newExp2

showExpression :: Expression -> String
showExpression (Number a) = show a
showExpression (Variable x) = x
showExpression (Add exp1 exp2) = "+ " ++ (showExpression exp1) ++ " " ++ (showExpression exp2)
showExpression (Subtract exp1 exp2) = "- " ++ (showExpression exp1) ++ " " ++ (showExpression exp2)
showExpression (Multiply exp1 exp2) = "* " ++ (showExpression exp1) ++ " " ++ (showExpression exp2)

showAnswer :: (Int, String) -> String
showAnswer (i, input) =
  "Case "++ (show i) ++ ": " ++
    (showExpression $ simplifyExpression $ parseExpression $ words input)

main = interact ((++"\n") . L.intercalate "\n" . map showAnswer . zip [1..] . lines)