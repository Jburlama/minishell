![image](https://github.com/user-attachments/assets/62d0b450-cca0-4a0b-b7e5-c975555ac3b7)


# This project is about creating a command-line shell, that mimics the behavior of bash.

# Our shell does:

• Displays a prompt when waiting for a new command.

• Has a working history.

• Can search and launch the right executable (based on the PATH variable or using a relative or an absolute path).

• Handles ’ (single quote) and  " (double quote)

• Redirections:

   - **<** redirect input.
   
   - **>** redirect output.
  
   - **>>** redirect output in append mode.

   - **<<** heardoc.

• Pipes (| character).

• Environment variables ($ followed by a sequence of characters).

• $?, expand to the exit status of the most recently executed foreground pipeline.

• **ctrl-C**, **ctrl-D**,  **ctrl-\\**

• The following builtins:

   - **echo with option -n**

   - **cd**

   - **pwd**

   - **export**

   - **unset**

   - **env**

   - **exit**

• && and || with parenthesis for priorities.

• Wildcards *.