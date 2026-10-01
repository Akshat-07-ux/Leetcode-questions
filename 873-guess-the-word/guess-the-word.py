# """
# This is Master's API interface.
# You should not implement it, or speculate about its implementation
# """
# class Master:
#     def guess(self, word: str) -> int:

class Solution:
    def findSecretWord(self, words: List[str], master: 'Master') -> None:

        def match_count(w1, w2):
            return sum(c1 == c2 for c1, c2 in zip(w1, w2))

        students = words
        for _ in range(30):
            if not students:
                return None


            best_w = students[0]
            min_max = len(students)

            for w1 in students:
                counts = [0] * 7
                for w2 in students:
                    counts[match_count(w1, w2)] += 1


                max_grp = max(counts)
                if max_grp < min_max:
                    min_max = max_grp
                    best_w = w1

            matches = master.guess(best_w)
            if matches == 6:
                return 

            students = [w for w in students if match_count(best_w, w) == matches]        