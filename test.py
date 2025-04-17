import os

msg_dir = r'/home/kvothe/ros/src/messages/msg'

print("="*40 + "\n")
for filename in os.listdir(msg_dir):
    if filename.endswith('.msg'):
        print(f"Message file: {filename}")
        with open(os.path.join(msg_dir, filename), 'r') as file:
            content = file.read()
            print(content)
            print("="*40 + "\n")
