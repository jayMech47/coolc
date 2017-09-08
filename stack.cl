-- A line commnent for testing
(*
 *  CS164 Fall 94
 *
 *  Programming Assignment 1
 *    Implementation of a simple stack machine.
 *
 *  Skeleton file
 *)

class Node {
   next : Node;
   value : String;

   init(val : String, nextNode : Node) : Node {
      {
      next <- nextNode;
      value <- val;
      self;
      }
   };
   next() : Node {
      next
   };
   value() : String {
      value
   };
};

class StackObject inherits IO {
   head : Node;

   push(val : String) : String {
      {
      head <- (new Node).init(val, head);
      val;
      }
   };

   pop() : String {
   let
   tempString : String
   in
      {
         tempString <- head.value();
         head <- head.next();
         tempString;
      }
   };

   isEmpty() : Bool {
      isvoid head
   };

   print() : Object {
   let 
   tempNode : Node
   in {
      tempNode <- head;
      while not isvoid tempNode.next() loop{
         out_string(tempNode.value());
         out_string("\n");
         tempNode <- tempNode.next();
      }pool;
      out_string(tempNode.value());
      out_string("\n");
   }
   };
};

class Main inherits IO {

   main() : Object {
   let

   inVal : String,
   so : StackObject,
   tmpString1 : String,
   tmpString2 : String,
   a2i : A2I
   in {
      so <- (new StackObject);
      a2i <- (new A2I);

      out_string(">");
      inVal <- in_string();

      while not inVal = "x" loop{
         if inVal = "e" then
            if so.isEmpty()  then
               0
            else
               {
               tmpString1 <- so.pop();
               if tmpString1 = "s" then
                  {
                  tmpString1 <- so.pop();
                  tmpString2 <- so.pop();
                  so.push(tmpString1);
                  so.push(tmpString2);
                  }
               else if tmpString1 = "+" then
                  {
                  tmpString1 <- so.pop();
                  tmpString2 <- so.pop();
                  tmpString1 <- a2i.i2a(a2i.a2i(tmpString1) + a2i.a2i(tmpString2));
                  so.push(tmpString1);
                  }
               else
                  {
                  so.push(tmpString1);
                  }
               fi
               fi;
               }
            fi
         else if inVal = "p" then
            {
            so.pop();
            }
         else if inVal = "d" then
            {
            so.print();
            }
         else
            {
            so.push(inVal);
            }
         fi
         fi
         fi;

         out_string("\n>");
         inVal <- in_string();
      }pool;

   }
   };
};
